#pragma once

#include "IDirWalker.h"

class DirWalker: public IDirWalker
{
public:
	DirWalker(std::filesystem::path root, bool onlyFiles = true);

	DirWalker(DirWalker &&) noexcept = default;
	DirWalker &operator =(DirWalker &&) noexcept = default;

	std::filesystem::path root() const override;
	std::filesystem::path next() override;

private:
	bool m_onlyFiles;
	std::filesystem::path m_root;
	std::filesystem::recursive_directory_iterator m_dirIter;
};

inline DirWalker::DirWalker(std::filesystem::path root, bool onlyFiles):
	m_onlyFiles{onlyFiles},
	m_root{std::move(root)},
	m_dirIter{m_root}
{}

inline std::filesystem::path DirWalker::root() const { return m_root; }

inline std::filesystem::path DirWalker::next()
{
	if (m_dirIter == decltype(m_dirIter){}) return {};

	for (; m_dirIter != std::filesystem::recursive_directory_iterator{}; ++m_dirIter)
		if (m_dirIter->is_regular_file() /*&& m_dirIter->path().extension() == ".cpp"*/)
		{
			const auto filepath{m_dirIter->path()};
			++m_dirIter;
			return filepath;
		}

	return {};
}
