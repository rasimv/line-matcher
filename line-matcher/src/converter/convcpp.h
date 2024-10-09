#pragma once

#include <cstdint>

using utf8_t = uint8_t;
using utf16_t = uint16_t;

extern "C"
{
	size_t utf16_to_utf8(const utf16_t* utf16, size_t utf16_len, utf8_t* utf8, size_t utf8_len);
	size_t utf8_to_utf16(utf8_t const* utf8, size_t utf8_len, utf16_t* utf16, size_t utf16_len);
}
