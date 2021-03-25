#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include "device_context.h"
#include "win32_helper.h"

namespace zee {
	class application
	{
	public:
		handle_t create(int x, int y, int width, int height);
		handle_t create(int x, int y, int pixel_size);
		void on_paint(UINT iMessage, WPARAM wParam, LPARAM lParam);

		void create_back_buffer(zee::uint32 width, zee::uint32 height);
		void create_back_buffer();

	public:
		void draw_line(HDC dc, POINT from, POINT to);
		void set_pixel(POINT point, COLORREF color);

	private:
		handle_t create_impl();
		void begin_play();
		void DrawLine_DDA(POINT start_pt, POINT end_pt, COLORREF color);
		void DrawLine_Bresenhem(POINT start_pt, POINT end_pt, COLORREF color);

	public:
		zee::device_context img_buffer;
		
		HWND MyhWnd;

		int x;
		int y;
		int width;
		int height;

		HPEN pen;
		int pixel_size;
		int grid_thickness;

		struct PixelPr {
			bool operator()(const POINT& l, const POINT& r) const {
				if (l.x < r.x) return true;
				else if (l.x > r.x) return false;

				return l.y < r.y;
			}
		};

		using pixel_map_type = std::map<POINT, COLORREF, PixelPr>;
		std::vector<pixel_map_type> lines;
		bool b_is_down = false;
		point_t mouse_start;
		point_t mouse_end;
	};
}//namespace zee 