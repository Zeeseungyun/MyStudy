#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include "imagebuffer.h"

class ApplicationRasterizer
{
public:
	/*
		CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y,
		nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
	*/
	HWND CreateAppWindow(int x, int y, int width, int height);
	HWND CreateAppWindow(int x, int y, int pixel_size);
	void OnPaint(UINT iMessage, WPARAM wParam, LPARAM lParam);

	void create_back_buffer(zee::uint32 width, zee::uint32 height);
	void create_back_buffer();

public:
	void DrawLine(HDC dc, POINT from, POINT to);
	void SetPixel(POINT point, COLORREF color);

private:
	HWND CreateAppWindow_Impl();
	void BeginPlay();
	void DrawLine_DDA(POINT start_pt, POINT end_pt, COLORREF color);
	void DrawLine_Bresenhem(POINT start_pt, POINT end_pt, COLORREF color);

public:
	zee::imagebuffer img_buffer;

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
	POINT mouse_start;
	POINT mouse_end;
};

