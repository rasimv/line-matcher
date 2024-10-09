#pragma once

#include <string>
#include <filesystem>

class IFileReader
{
public:
	virtual bool ok() const = 0;
	virtual std::filesystem::path filepath() const = 0;
	virtual std::string getline() = 0;
	virtual bool eof() const = 0;

	virtual ~IFileReader() noexcept = default;

protected:
	IFileReader() = default;

	IFileReader(const IFileReader &) = delete;
	IFileReader &operator =(const IFileReader &) = delete;

	IFileReader(IFileReader &&) noexcept = default;
	IFileReader &operator =(IFileReader &&) noexcept = default;
};

using IFileReaderUPtr = std::unique_ptr<IFileReader>;
