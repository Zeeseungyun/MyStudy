#pragma once
#include <type_traits>
#include <cstdint>
#include <cfloat>
#include <numeric>

namespace zee {
	typedef void* handle_t;

	typedef std::int8_t int8;
	typedef std::int16_t int16;
	typedef std::int32_t int32;
	typedef std::int64_t int64;

	typedef std::uint8_t uint8;
	typedef std::uint16_t uint16;
	typedef std::uint32_t uint32;
	typedef std::uint64_t uint64;

	handle_t get_main_window_handle();
	handle_t get_instance_handle();

	typedef uint32 color_t;
	inline constexpr color_t make_color(uint8 r, uint8 g, uint8 b) {
		return ((color_t)(((uint8)(r) | ((uint16)((uint8)(g)) << 8)) | (((uint32)(uint8)(b)) << 16)));
	}

namespace colors {
	constexpr color_t red	= make_color(255, 0, 0);
	constexpr color_t green = make_color(0, 255, 0);
	constexpr color_t blue	= make_color(0, 0, 255);
	constexpr color_t black = make_color(0, 0, 0);
	constexpr color_t white = make_color(255, 255, 255);
}//namespace colors 

} //namespace zee 