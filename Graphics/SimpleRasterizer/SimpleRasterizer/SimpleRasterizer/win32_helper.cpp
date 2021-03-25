#include "win32_helper.h"
namespace zee {

	rect_t& rect_t::operator+=(const RECT& rc) noexcept {
		return *this = *this + rc;
	}

	rect_t& rect_t::operator-=(const RECT& rc) noexcept {
		return *this = *this - rc; 
	}

	rect_t& rect_t::operator*=(LONG s) noexcept {
		return *this = *this * s;
	}

	rect_t& rect_t::operator/=(LONG s) {
		return *this = *this / s;
	}

	point_t& point_t::operator+=(const POINT& pt) noexcept {
		return *this = *this + pt;
	}

	point_t& point_t::operator-=(const POINT& pt) noexcept {
		return *this = *this - pt;
	}

	point_t& point_t::operator*=(LONG s) noexcept {
		return *this = *this * s;
	}

	point_t& point_t::operator/=(LONG s) {
		return *this = *this / s;
	}

	int32 rect_t::width() const noexcept {
		return zee::width(*this);
	}

	int32 rect_t::height() const noexcept {
		return zee::height(*this);
	}

}//namespace zee 
