#include "imagebuffer.h"
#include "win32_helper.h"
#include <exception>

namespace zee {
	imagebuffer::imagebuffer() noexcept
		: dc(nullptr), ob(nullptr)
		, width_(0), height_(0) {

	}

	imagebuffer::imagebuffer(const imagebuffer& other)
		: imagebuffer(other.width(), other.height()) {
		if (is_valid()) {
			//todo:: bitblt
		}
	}

	imagebuffer::imagebuffer(imagebuffer&& other) noexcept 
		: imagebuffer() {
		swap(*this, other);
	}

	imagebuffer::imagebuffer(uint32 width, uint32 height, color_t clear_color)
		: imagebuffer() {
		if (!create(width, height, clear_color)) {
			throw std::exception("invalid param");
		}
		//todo:: clear color
	}

	imagebuffer::~imagebuffer() {
		clear();
	}

	imagebuffer& imagebuffer::operator=(const imagebuffer& other) {
		if (this != &other) {
			clear();
			if (other.is_valid()) {
				//todo:: copy
			}
		}
		return *this;
	}

	imagebuffer& imagebuffer::operator=(imagebuffer&& other) noexcept {
		if (this != &other) {
			clear();
			swap(*this, other);
		}
		return *this;
	}

	bool imagebuffer::create(uint32 new_width, uint32 new_height, color_t clear_color) {
		if (width() != new_width && height() != new_height && new_width && new_height) {
			clear();
			if (auto wnd = get_main_window_handle())
			{
				width_ = new_width;
				height_ = new_height;
				HDC temp_dc = GetDC((HWND)wnd);
				dc = CreateCompatibleDC(temp_dc);
				ob = SelectObject((HDC)dc, CreateCompatibleBitmap(temp_dc, (int)new_width, (int)new_height));
				ReleaseDC((HWND)wnd, temp_dc);
			}
			return true;
		}
		return false;
	}

	void imagebuffer::clear() {
		if (dc) {
			DeleteObject(SelectObject((HDC)dc, (HGDIOBJ)ob));
			DeleteDC((HDC)dc);
			dc = ob = nullptr;
		}
	}

	void imagebuffer::draw(const imagebuffer& from_image, int32 to_x, int32 to_y, int32 from_x, int32 from_y) {
		if (from_image.is_valid() && is_valid()) {
			BitBlt((HDC)dc, to_x, to_y, (int)from_image.width(), (int)from_image.height(), (HDC)from_image.dc, from_x, from_y, SRCCOPY);
		} else {
			throw std::exception("from image is invalid.");
		}
	}

	void imagebuffer::fill(color_t color) {
		if (is_valid()) {
			const RECT rc = make_rect(width(), height());
			FillRect((HDC)get_dc(), &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		}
	}

	void swap(imagebuffer& l, imagebuffer& r) {
		std::swap(l.width_, r.width_);
		std::swap(l.height_, r.height_);
		std::swap(l.dc, r.dc);
		std::swap(l.ob, r.ob);
	}

} //namespace zee 