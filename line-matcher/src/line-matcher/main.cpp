#include "core/DirWalker.hpp"
#include "core/FileReaderFactory.hpp"
#include "core/LineMatcher.h"
#include "core/Output.hpp"
#include <string>
#include <iostream>

#ifndef _WIN32

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Usage: line-matcher [pattern] [root]" << std::endl;
		return 1;
	}

	try
	{
		std::regex pattern{argv[1], std::regex_constants::grep};
		DirWalker dirWalker{argv[2]};
		FileReaderFactory fileReaderFactory;
		Output output{std::cout};

		LineMatcher lm{pattern, &dirWalker, &fileReaderFactory, &output};

		lm.start();
		lm.wait();
	}
	catch (const std::exception &a)
	{
		std::cout << a.what() << std::endl;
		return -1;
	}

	return 0;
}

#else

// The encoding conversion features of the C++ Standard Library have been deprecated
#include <converter/convcpp.h>
#include <Windows.h>	// For SetConsoleOutputCP(CP_UTF8)

int wmain(int argc, wchar_t *argv[])
{
	if (argc < 3)
	{
		std::cout << "Usage: line-matcher [pattern] [root]" << std::endl;
		return 1;
	}

	::SetConsoleOutputCP(CP_UTF8);	// Output unicode paths

	try
	{
		const std::wstring patternUtf16{argv[1]};
		std::string patternUtf8(4 * std::size(patternUtf16), 0);
		const auto count = utf16_to_utf8(reinterpret_cast<const utf16_t*>(patternUtf16.data()),
											std::size(patternUtf16),
											reinterpret_cast<utf8_t *>(patternUtf8.data()),
											patternUtf8.size());
		patternUtf8.resize(count);

		std::regex pattern{patternUtf8, std::regex_constants::grep};
		DirWalker dirWalker{argv[2]};
		FileReaderFactory fileReaderFactory;
		Output output{std::cout};

		LineMatcher lm{pattern, &dirWalker, &fileReaderFactory, &output};

		lm.start();
		lm.wait();
	}
	catch (const std::exception &a)
	{
		std::cout << a.what() << std::endl;
		return -1;
	}

	return 0;
}

#endif
