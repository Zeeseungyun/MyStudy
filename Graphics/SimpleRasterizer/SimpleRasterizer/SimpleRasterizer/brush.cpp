#include "brush.h"
#include "stdafx.h"

namespace zee {
	void swap(brush& l, brush& r) noexcept {
		std::swap(l.handle, r.handle);
	}

	std::shared_ptr<brush> create_solid_brush(color_t color) noexcept {
		std::shared_ptr<brush> ret = std::make_shared<brush>();
		ret->handle = CreateSolidBrush(color);
		return ret;
	}

	std::shared_ptr<brush> create_pattern_brush(bitmap color) {
		return brush();
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