#pragma once

#include "IOutput.h"
#include <iostream>
#include <cassert>
#include <variant>

class Output: public IOutput
{
public:
	Output(std::ostream &outputStream);
	Output(std::wostream &outputStream);

	Output(Output &&) noexcept = default;
	Output &operator =(Output &&) noexcept = default;

	void log(const std::string &line) override;
	void log(const std::wstring &line) override;

private:
	bool check() const;

	std::variant<std::ostream *, std::wostream *> m_outputStream;
};

inline Output::Output(std::ostream &outputStream):
	m_outputStream{&outputStream}
{
	assert(std::get_if<std::ostream *>(&m_outputStream) != nullptr &&
			*std::get_if<std::ostream *>(&m_outputStream) != nullptr);
}

inline Output::Output(std::wostream &outputStream):
	m_outputStream{&outputStream}
{
	assert(std::get_if<std::wostream *>(&m_outputStream) != nullptr &&
			*std::get_if<std::wostream *>(&m_outputStream) != nullptr);
}

inline void Output::log(const std::string &line)
{
	assert(check());

	// Only this branch is used for now
	const auto outputStream = std::get_if<std::ostream *>(&m_outputStream);
	if (outputStream != nullptr)
	{
		**outputStream << line << '\n';
		return;
	}

	// TODO: Implement utf8->utf16 or utf8->utf32 conversion depending on platform
}

inline void Output::log(const std::wstring &line)
{
	assert(check());

	const auto outputStreamW = std::get_if<std::wostream *>(&m_outputStream);
	if (outputStreamW != nullptr)
	{
		**outputStreamW << line << L'\n';
		return;
	}
	
	// TODO: Implement utf16->local8bit or utf32->utf8 conversion depending on platform
}

bool Output::check() const
{
	return std::get_if<std::ostream*>(&m_outputStream) != nullptr &&
			*std::get_if<std::ostream*>(&m_outputStream) != nullptr ||
			std::get_if<std::wostream*>(&m_outputStream) != nullptr &&
			*std::get_if<std::wostream*>(&m_outputStream) != nullptr;
}
