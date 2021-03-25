#pragma once
#include "base.h"
#include "object.h"

namespace zee {

	class device_context : public object {
		friend void swap(device_context& l, device_context& r);
	public:
		device_context() noexcept;
		device_context(const device_context& other);
		device_context(device_context&& other) noexcept;

		explicit device_context(uint32 width, uint32 height, color_t clear_color = colors::black);
		~device_context();

		device_context& operator=(const device_context& other);
		device_context& operator=(device_context&& other) noexcept;

		bool create(uint32 width, uint32 height, color_t clear_color = colors::black);
		void clear() final;

		uint32 width() const { return width_; }
		uint32 height() const { return height_; }
		bool is_valid() const { return width() && height() && dc; }

		void draw(const device_context& from_image, int32 to_x, int32 to_y, int32 from_x = 0, int32 from_y = 0);
		void fill(color_t color = colors::black);

		handle_t get_dc() const { return dc; }
		handle_t get_handle(render_handle_type type) const { 
			return old_handles[(uint8)type];
		}

	private:
		handle_t dc;
		handle_t old_handles[(uint8)render_handle_type::count];
		uint32 width_, height_;
	};

	void swap(device_context& l, device_context& r);
}