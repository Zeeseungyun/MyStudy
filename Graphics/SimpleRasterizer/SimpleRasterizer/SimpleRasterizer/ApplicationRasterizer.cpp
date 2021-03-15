#include "Rasterizing.h"
extern HINSTANCE g_hInst;
extern LPCTSTR lpszClass;
template<typename HandleT>
HandleT MySelectObject(HDC hdc, HandleT t)
{
	return (HandleT)SelectObject(hdc, (HandleT)t);
}

void ApplicationRasterizer::CreateBackBuffer(int x, int y)
{
	if (backDC)
	{
		DeleteObject(MySelectObject(backDC, old_backbitmap));
		old_backbitmap = NULL;
		DeleteDC(backDC);
		backDC = NULL;
		CreateBackBuffer(x, y);
	}
	else
	{
		HDC temphDC = GetDC(MyhWnd);
		backDC = CreateCompatibleDC(temphDC);
		HBITMAP newBITMAP = CreateCompatibleBitmap(temphDC, x, y);
		old_backbitmap = MySelectObject(backDC, newBITMAP);
		ReleaseDC(MyhWnd, temphDC);
	}
}

HWND ApplicationRasterizer::CreateAppWindow(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->pixel_size = width * 0.03f;
	this->grid_thickness = 2;

	return CreateAppWindow_Impl();
}

HWND ApplicationRasterizer::CreateAppWindow(int x, int y, int pixel_size)
{
	this->x = x;
	this->y = y;
	this->pixel_size = pixel_size;
	this->width = pixel_size * 15;
	this->height = pixel_size * 15;

	return CreateAppWindow_Impl();
}

HWND ApplicationRasterizer::CreateAppWindow_Impl()
{
	this->grid_thickness = 2;

	MyhWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		x, y, width, height,
		NULL, (HMENU)NULL, g_hInst, NULL);

	pen = CreatePen(PS_SOLID, this->grid_thickness, 0);
	RECT ClientRect;
	GetClientRect(MyhWnd, &ClientRect);
	CreateBackBuffer(ClientRect.right, ClientRect.bottom);
	return MyhWnd;
}

void ApplicationRasterizer::OnPaint(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	BeginPlay();
	RECT ClientRect;
	GetClientRect(MyhWnd, &ClientRect);
	FillRect(backDC, &ClientRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	PAINTSTRUCT paint_struct; 
	HDC realDC = BeginPaint(MyhWnd, &paint_struct);

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
		DrawLine(backDC, { pixel_count * pixel_size, 0 }, { pixel_count * pixel_size, height });
		++pixel_count;
	}
	pixel_count = 0;
	while (pixel_count * pixel_size <= height) {
		DrawLine(backDC, { 0, pixel_count * pixel_size }, { width, pixel_count * pixel_size });
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
			DrawLine(backDC, start_pt, end_pt);
		}
	}

	SelectObject(backDC, old_pen);
	BitBlt(realDC, 0, 0, ClientRect.right, ClientRect.bottom, backDC, 0, 0, SRCCOPY);
	EndPaint(MyhWnd, &paint_struct);
}

void ApplicationRasterizer::DrawLine(HDC dc, POINT from, POINT to)
{
	MoveToEx(dc, from.x, from.y, NULL);
	LineTo(dc, to.x, to.y);
}

void ApplicationRasterizer::SetPixel(POINT point, COLORREF color)
{
	lines.back()[point] = color;
}
