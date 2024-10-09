#pragma once

#include "IFileReaderFactory.h"
#include "IDirWalker.h"
#include "IOutput.h"
#include <regex>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>

class LineMatcher
{
	struct Subtask
	{
		size_t lineCount = 0;
		IFileReaderUPtr fileReader;
	};

	using SubtaskUPtr = std::unique_ptr<Subtask>;

public:
	// Pointer arguments must not be nullptr.
	// All passed objects must outlive this LineMatcher object
	LineMatcher(std::regex pattern, IDirWalker *dirWalker,
				IFileReaderFactory *fileReaderFactory, IOutput *output);

	~LineMatcher();

	void start(size_t numberOfThread = std::thread::hardware_concurrency());
	void wait();

	void setForwardSlashes(bool value) { m_forwardSlashes = value; }

private:
	void worker(size_t i);

	IFileReaderUPtr newFileReader(const std::filesystem::path &filepath);
	void output(const std::filesystem::path &filepath,
											size_t lineCount, const std::string &line);

	std::filesystem::path relative(const std::filesystem::path &root,
									const std::filesystem::path &full);

	std::regex m_pattern;
	IDirWalker *m_dirWalker = nullptr;
	IFileReaderFactory *m_fileReaderFactory = nullptr;
	IOutput *m_output = nullptr;

	std::atomic_bool m_dirExhausted = false;
	std::atomic_size_t m_waitCount = 0;
	std::list<SubtaskUPtr> m_subtasks;

	std::mutex m_dirWalkerMtx, m_subtasksMtx, m_outputMtx;
	std::condition_variable m_finishCV;

	std::mutex m_fileReaderFactoryMtx;	// For testing only

	std::vector<std::thread> m_threads;

	bool m_forwardSlashes = false;
};
