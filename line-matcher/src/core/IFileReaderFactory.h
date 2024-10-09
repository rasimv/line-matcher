#pragma once

#include "IFileReader.h"

#include <memory>

class IFileReaderFactory
{
public:
	virtual IFileReaderUPtr create(const std::filesystem::path &filepath) = 0;

	virtual ~IFileReaderFactory() noexcept = default;

protected:
	IFileReaderFactory() = default;

	IFileReaderFactory(const IFileReaderFactory &) = delete;
	IFileReaderFactory &operator =(const IFileReaderFactory &) = delete;

	IFileReaderFactory(IFileReaderFactory &&) noexcept = default;
	IFileReaderFactory &operator =(IFileReaderFactory &&) noexcept = default;
};
