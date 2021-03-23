#include "win32_helper.h"

bool is_valid_rect(const RECT& rc) {
	return rc.left <= rc.right
		&& rc.left <= rc.bottom;
}

zee::uint32 rect_width(const RECT& rc) {
	return rc.right - rc.left;
}

zee::uint32 rect_height(const RECT& rc) {
	return rc.bottom - rc.top;
}

RECT make_rect(zee::uint32 width, zee::uint32 height) {
	return RECT { 0, 0, (LONG)width, (LONG)height };
}