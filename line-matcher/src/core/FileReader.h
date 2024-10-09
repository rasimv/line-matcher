#pragma once

#include "IFileReader.h"
#include <fstream>

class FileReader: public IFileReader
{
	friend class FileReaderFactory;

public:
	FileReader(FileReader &&) noexcept = default;
	FileReader &operator =(FileReader &&) noexcept = default;

	bool ok() const override;
	std::filesystem::path filepath() const override;
	std::string getline() override;
	bool eof() const override;

protected:
	FileReader(std::filesystem::path filepath);

	std::filesystem::path m_filepath;
	std::ifstream m_ifstream;
};

inline bool FileReader::ok() const
{
	return m_ifstream.is_open() && !m_ifstream.bad();
}

inline std::filesystem::path FileReader::filepath() const
{
	return m_filepath;
}

inline std::string FileReader::getline()
{
	if (!ok()) return {};

	std::string line;
	std::getline(m_ifstream, line);

	return line;
}

inline bool FileReader::eof() const { return m_ifstream.eof(); }

inline FileReader::FileReader(std::filesystem::path filepath):
	m_filepath{filepath},
	m_ifstream{filepath, std::ios::in | std::ios::binary}
{}
