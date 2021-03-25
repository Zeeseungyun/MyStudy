#include "application.h"
#include "win32_helper.h"

extern HINSTANCE g_hInst;
extern LPCTSTR lpszClass;

namespace zee {
	template<typename HandleT>
	HandleT MySelectObject(HDC hdc, HandleT t)
	{
		return (HandleT)SelectObject(hdc, (HandleT)t);
	}

	void application::create_back_buffer(zee::uint32 width, zee::uint32 height)
	{
		img_buffer.create((zee::uint32)width, (zee::uint32)height);
	}

	void application::create_back_buffer() {
		create_back_buffer(width, height);
	}

	handle_t application::create(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->pixel_size = width * 0.03f;
		this->grid_thickness = 2;

		return create_impl();
	}

	handle_t application::create(int x, int y, int pixel_size)
	{
		this->x = x;
		this->y = y;
		this->pixel_size = pixel_size;
		this->width = pixel_size * 15;
		this->height = pixel_size * 15;

		return create_impl();
	}

	handle_t application::create_impl()
	{
		this->grid_thickness = 2;
		MyhWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
			x, y, width, height,
			NULL, (HMENU)NULL, (HINSTANCE)get_instance_handle(), NULL);

		pen = CreatePen(PS_SOLID, this->grid_thickness, 0);
		return MyhWnd;
	}

	void application::on_paint(UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		begin_play();
		img_buffer.fill();
		HDC backDC = (HDC)img_buffer.get_dc();

		HBRUSH old_brush = (HBRUSH)SelectObject(backDC, GetStockObject(DC_BRUSH));

		for (const auto& pixels : lines) {
			if (size(pixels) > 0) {
				for (const auto& pixel : pixels) {
					SetDCBrushColor(backDC, pixel.second);
					int x = pixel.first.x * pixel_size;
					int y = pixel.first.y * pixel_size;
					Rectangle(backDC, x, y, x + pixel_size, y + pixel_size);
				}
			}
		}

		SelectObject(backDC, old_brush);

		HPEN old_pen = (HPEN)SelectObject(backDC, pen);

		int pixel_count = 0;
		while (pixel_count * pixel_size <= width) {
			draw_line(backDC, { pixel_count * pixel_size, 0 }, { pixel_count * pixel_size, height });
			++pixel_count;
		}
		pixel_count = 0;
		while (pixel_count * pixel_size <= height) {
			draw_line(backDC, { 0, pixel_count * pixel_size }, { width, pixel_count * pixel_size });
			++pixel_count;
		}

		for (const auto& pixels : lines) {
			if (size(pixels) > 0) {
				auto start_pt = begin(pixels)->first;
				start_pt.x *= pixel_size;
				start_pt.y *= pixel_size;

				start_pt.x += (pixel_size / 2);
				start_pt.y += (pixel_size / 2);

				auto end_pt = prev(end(pixels))->first;
				end_pt.x *= pixel_size;
				end_pt.y *= pixel_size;

				end_pt.x += (pixel_size / 2);
				end_pt.y += (pixel_size / 2);
				draw_line(backDC, start_pt, end_pt);
			}
		}

		SelectObject(backDC, old_pen);

		PAINTSTRUCT paint_struct;
		HDC realDC = BeginPaint(MyhWnd, &paint_struct);
		BitBlt(realDC, 0, 0, img_buffer.width(), img_buffer.height(), backDC, 0, 0, SRCCOPY);
		EndPaint(MyhWnd, &paint_struct);
	}


	void application::draw_line(HDC dc, POINT from, POINT to)
	{
		MoveToEx(dc, from.x, from.y, NULL);
		LineTo(dc, to.x, to.y);
	}

	void application::set_pixel(POINT point, COLORREF color)
	{
		lines.back()[point] = color;
	}

}//namespace zee 