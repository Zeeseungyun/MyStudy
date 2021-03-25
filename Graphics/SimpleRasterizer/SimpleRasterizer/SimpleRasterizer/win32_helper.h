#pragma once
#include "base.h"
#include <Windows.h>
namespace zee {
	struct rect_t : public RECT {
		constexpr rect_t() noexcept : rect_t(0, 0, 0, 0) { }
		constexpr rect_t(LONG left, LONG top, LONG right, LONG bottom) noexcept 
			: RECT{ left, top, right, bottom } { }
		constexpr explicit rect_t(LONG width, LONG height) noexcept
			: RECT{ 0, 0, width, height } { }
		constexpr rect_t(const RECT& rc) noexcept : RECT(rc) { }

		rect_t& operator=(const RECT& rc) noexcept {
			if (this != &rc) {
				left = rc.left; right = rc.right;
				bottom = rc.bottom; top = rc.top;
			}
			return *this;
		}

		int32 width() const noexcept;
		int32 height() const noexcept;

		rect_t& operator+=(const RECT& rc) noexcept;
		rect_t& operator-=(const RECT& rc) noexcept;
		rect_t& operator*=(LONG s) noexcept;
		rect_t& operator/=(LONG s);

		struct constants;
	};

	struct rect_t::constants {
		constexpr static rect_t zero = rect_t();
	};

	constexpr int32 width(const RECT& rc) noexcept { return rc.right - rc.left; }
	constexpr int32 height(const RECT& rc) noexcept { return rc.bottom - rc.top; }
	constexpr bool is_valid_rect(const RECT& rc) noexcept {
		return rc.left <= rc.right && rc.left <= rc.bottom;
	}

	constexpr rect_t operator+(const RECT& l, const RECT& r) noexcept {
		return rect_t{ l.left + r.left, l.top + r.top, l.right + r.right, l.bottom + r.bottom };
	}

	constexpr rect_t operator-(const RECT& l, const RECT& r) noexcept {
		return rect_t{ l.left - r.left, l.top - r.top, l.right - r.right, l.bottom - r.bottom };
	}

	constexpr rect_t operator*(const RECT& l, LONG s) noexcept {
		return rect_t{ l.left * s , l.top * s , l.right * s , l.bottom * s };
	}

	constexpr rect_t operator/(const RECT& l, LONG s) {
		return rect_t{ l.left / s , l.top / s , l.right / s , l.bottom / s };
	}

	struct point_t : public POINT {
		constexpr point_t() noexcept : point_t(0, 0) { }
		constexpr point_t(LONG x, LONG y) noexcept : POINT{ x, y } { }
		constexpr point_t(const POINT& pt) noexcept : POINT(pt) { }
		point_t& operator=(const POINT& pt) noexcept {
			x = pt.x; y = pt.y;
			return *this;
		}

		point_t& operator+=(const POINT& pt) noexcept;
		point_t& operator-=(const POINT& pt) noexcept;
		point_t& operator*=(LONG s) noexcept;
		point_t& operator/=(LONG s);

		struct constants;
	};

	struct point_t::constants {
		constexpr static point_t zero = point_t();
		constexpr static point_t unit_x = point_t(1, 0);
		constexpr static point_t unit_y = point_t(0, 1);
	};

	constexpr point_t operator+(const POINT& l, const POINT& r) noexcept {
		return point_t{ l.x + r.x , l.y + r.y };
	}

	constexpr point_t operator-(const POINT& l, const POINT& r) noexcept {
		return point_t{ l.x - r.x , l.y - r.y };
	}

	constexpr point_t operator*(const POINT& l, LONG s) noexcept {
		return point_t{ l.x * s , l.y * s };
	}

	constexpr point_t operator/(const POINT& l, LONG s) {
		return point_t{ l.x / s , l.y / s };
	}

}//namespace zee 
