#pragma once

class IOutput
{
public:
	virtual void log(const std::string &line) = 0;
	virtual void log(const std::wstring &line) = 0;

	virtual ~IOutput() noexcept = default;

protected:
	IOutput() = default;

	IOutput(const IOutput &) = delete;
	IOutput &operator =(const IOutput &) = delete;

	IOutput(IOutput &&) noexcept = default;
	IOutput &operator =(IOutput &&) noexcept = default;
};
