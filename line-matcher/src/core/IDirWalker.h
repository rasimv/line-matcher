#pragma once

#include <filesystem>

class IDirWalker
{
public:
	virtual std::filesystem::path root() const = 0;
	virtual std::filesystem::path next() = 0;

	virtual ~IDirWalker() noexcept = default;

protected:
	IDirWalker() = default;

	IDirWalker(const IDirWalker &) = delete;
	IDirWalker &operator =(const IDirWalker &) = delete;

	IDirWalker(IDirWalker &&) noexcept = default;
	IDirWalker &operator =(IDirWalker &&) noexcept = default;
};
