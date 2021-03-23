#pragma once
#include "base.h"

namespace zee {
	class imagebuffer
	{
		friend void swap(imagebuffer& l, imagebuffer& r);
	public:
		imagebuffer() noexcept;
		imagebuffer(const imagebuffer& other);
		imagebuffer(imagebuffer&& other) noexcept;

		explicit imagebuffer(uint32 width, uint32 height, color_t clear_color = colors::black);
		~imagebuffer();

		imagebuffer& operator=(const imagebuffer& other);
		imagebuffer& operator=(imagebuffer&& other) noexcept;

		bool create(uint32 width, uint32 height, color_t clear_color = colors::black);
		void clear();

		uint32 width() const { return width_; }
		uint32 height() const { return height_; }
		bool is_valid() const { return width() && height() && dc && ob; }

		void draw(const imagebuffer& from_image, int32 to_x, int32 to_y, int32 from_x = 0, int32 from_y = 0);
		void fill(color_t color = colors::black);

		handle_t get_dc() const { return dc; }

	private:
		handle_t dc;
		handle_t ob;
		uint32 width_, height_;
	};

	void swap(imagebuffer& l, imagebuffer& r);
}