#pragma once

#include "IFileReaderFactory.h"
#include "FileReader.h"

class FileReaderFactory: public IFileReaderFactory
{
public:
	FileReaderFactory() = default;

	FileReaderFactory(FileReaderFactory &&) noexcept = default;
	FileReaderFactory &operator =(FileReaderFactory &&) noexcept = default;

	IFileReaderUPtr create(const std::filesystem::path &filepath) override;
};

inline IFileReaderUPtr FileReaderFactory::create(const std::filesystem::path &filepath)
{
	return IFileReaderUPtr{new FileReader{filepath}};
}
