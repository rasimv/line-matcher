#include "LineMatcher.h"
#include <cassert>
#include <sstream>

LineMatcher::LineMatcher(std::regex pattern, IDirWalker *dirWalker,
							IFileReaderFactory *fileReaderFactory, IOutput *output):
	m_pattern{std::move(pattern)},
	m_dirWalker{dirWalker},
	m_fileReaderFactory{fileReaderFactory},
	m_output{output}
{
	assert(m_dirWalker != nullptr);
	assert(m_fileReaderFactory != nullptr);
	assert(m_output != nullptr);
}

LineMatcher::~LineMatcher()
{}

void LineMatcher::start(size_t numberOfThread)
{
	for (size_t i = 0; i < numberOfThread; ++i)
		m_threads.emplace_back(&LineMatcher::worker, this, i);
}

void LineMatcher::wait()
{
	for (auto &thread: m_threads) thread.join();
}

void LineMatcher::worker(size_t i)
{
	assert(m_dirWalker != nullptr &&
			m_fileReaderFactory != nullptr && m_output != nullptr);

	while (true)
	{
		SubtaskUPtr subtask;

		std::unique_lock<std::mutex> subtasksLock{m_subtasksMtx};

		if (!m_subtasks.empty())
		{
fetchSubtask:
			subtask = std::move(m_subtasks.back());
			m_subtasks.pop_back();

			subtasksLock.unlock();
		}
		else if (!m_dirExhausted)
		{
			subtasksLock.unlock();

			std::unique_lock<std::mutex> dirWalkerLock{m_dirWalkerMtx};

			const auto next{m_dirWalker->next()};

			dirWalkerLock.unlock();

			if (next.empty())
			{
				m_dirExhausted = true;

				continue;
			}

			subtask = std::make_unique<Subtask>();
			subtask->fileReader = newFileReader(next);
		}
		else
		{
			if (++m_waitCount == std::size(m_threads))
			{
				m_finishCV.notify_all();

				break;
			}

			m_finishCV.wait(subtasksLock, [&]() { return !m_subtasks.empty() ||
											m_waitCount == std::size(m_threads); });

			if (m_subtasks.empty()) break;

			--m_waitCount;

			goto fetchSubtask;
		}

		std::string line{subtask->fileReader->getline()};

		const auto lineCount = ++subtask->lineCount;
		const auto filepath{subtask->fileReader->filepath()};

		if (!subtask->fileReader->ok())
		{
			output(filepath, -1, "File read error");
			continue;
		}

		if (line.empty() && subtask->fileReader->eof()) continue;

		if (!line.empty() && *std::rbegin(line) == '\r') line.pop_back();

		subtasksLock.lock();

		m_subtasks.push_back(std::move(subtask));

		subtasksLock.unlock();

		m_finishCV.notify_one();

		if (std::regex_search(line, m_pattern)) output(filepath, lineCount, line);
	}
}

IFileReaderUPtr LineMatcher::newFileReader(const std::filesystem::path &filepath)
{
	assert(m_fileReaderFactory != nullptr);

	std::unique_lock<std::mutex> fileReaderFactoryLock{m_fileReaderFactoryMtx};

	return m_fileReaderFactory->create(filepath);
}

void LineMatcher::output(const std::filesystem::path &filepath,
									size_t lineCount, const std::string &line)
{
	assert(m_output != nullptr && m_dirWalker != nullptr);

	const auto relativePath{relative(m_dirWalker->root(), filepath)};
	const auto relativeInUtf8{m_forwardSlashes?
								relativePath.generic_u8string(): relativePath.u8string()};
	std::string relativeAsStdString(std::begin(relativeInUtf8),
										std::end(relativeInUtf8));	// C++17 & C++20

	std::stringstream stringStream;		// utf8 only for now. std::wstringstream can be
										// more efficient on Windows, where wide strings
										// are typically utf16, the native encoding
	stringStream << relativeAsStdString;
	if (lineCount != -1) stringStream << ":" << lineCount;
	stringStream << ":" << line;

	std::unique_lock<std::mutex> outputLock{m_outputMtx};

	m_output->log(stringStream.str());
}

std::filesystem::path LineMatcher::relative(const std::filesystem::path &root,
											const std::filesystem::path &full)
{
	auto f{std::begin(full)};
	for (auto r{std::begin(root)}; r != std::end(root); ++f, ++r)
		if (f == std::end(full)) return full;

	std::filesystem::path relative;
	for (; f != std::end(full); ++f)
		relative /= *f;

	return relative;
}
