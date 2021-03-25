#include "brush.h"
#include "stdafx.h"

namespace zee {
	void swap(brush& l, brush& r) {
		std::swap(l.handle, r.handle);
	}

	brush create_solid_brush(color_t color) {
		brush ret;
		ret.handle = CreateSolidBrush(color);
		
		return ret;
	}

	brush::brush(brush&& other) noexcept : brush() {

	}

	brush::brush(const brush& other) : brush() {

	}

	brush& brush::operator=(brush&& other) noexcept {
		return *this;
	}

	brush& brush::operator=(const brush& other) {
		return *this;
	}

	void brush::clear()	{
		
	}

	brush::~brush() {

	}
}//namespace zee 