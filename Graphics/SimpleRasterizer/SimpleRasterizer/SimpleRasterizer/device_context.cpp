#include "device_context.h"
#include "win32_helper.h"
#include <exception>

namespace zee {
	device_context::device_context() noexcept
		: dc(nullptr), old_handles{nullptr,}
		, width_(0), height_(0) {
	}

	device_context::device_context(const device_context& other)
		: device_context(other.width(), other.height()) {
		if (is_valid()) {
			//todo:: bitblt
		}
	}

	device_context::device_context(device_context&& other) noexcept 
		: device_context() {
		swap(*this, other);
	}

	device_context::device_context(uint32 width, uint32 height, color_t clear_color)
		: device_context() {
		if (!create(width, height, clear_color)) {
			throw std::exception("invalid param");
		}
		//todo:: clear color
	}

	device_context::~device_context() {
		clear();
	}

	device_context& device_context::operator=(const device_context& other) {
		if (this != &other) {
			clear();
			if (other.is_valid()) {
				//todo:: copy
			}
		}
		return *this;
	}

	device_context& device_context::operator=(device_context&& other) noexcept {
		if (this != &other) {
			clear();
			swap(*this, other);
		}
		return *this;
	}

	bool device_context::create(uint32 new_width, uint32 new_height, color_t clear_color) {
		if (width() != new_width && height() != new_height && new_width && new_height) {
			clear();
			if (auto wnd = get_main_window_handle())
			{
				width_ = new_width;
				height_ = new_height;
				HDC temp_dc = GetDC((HWND)wnd);
				dc = CreateCompatibleDC(temp_dc);
				old_handles[(uint8)render_handle_type::bitmap] = SelectObject((HDC)dc, CreateCompatibleBitmap(temp_dc, (int)new_width, (int)new_height));
				ReleaseDC((HWND)wnd, temp_dc);
			}
			return true;
		}
		return false;
	}

	void device_context::clear() {
		if (dc) {
			for (auto& oh : old_handles) {
				if (oh) {
					DeleteObject(SelectObject((HDC)dc, (HGDIOBJ)oh));
				}
				oh = nullptr;
			}
			DeleteDC((HDC)dc);
			dc = nullptr;
		}
	}

	void device_context::draw(const device_context& from_image, int32 to_x, int32 to_y, int32 from_x, int32 from_y) {
		if (from_image.is_valid() && is_valid()) {
			BitBlt((HDC)dc, to_x, to_y, (int)from_image.width(), (int)from_image.height(), (HDC)from_image.dc, from_x, from_y, SRCCOPY);
		} else {
			throw std::exception("from image is invalid.");
		}
	}

	void device_context::fill(color_t color) {
		if (is_valid()) {
			rect_t rc((LONG)width(), (LONG)height());
			FillRect((HDC)get_dc(), &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		}
	}

	void swap(device_context& l, device_context& r) {
		std::swap(l.width_, r.width_);
		std::swap(l.height_, r.height_);
		std::swap(l.dc, r.dc);
		std::swap(l.old_handles, r.old_handles);
	}

} //namespace zee 