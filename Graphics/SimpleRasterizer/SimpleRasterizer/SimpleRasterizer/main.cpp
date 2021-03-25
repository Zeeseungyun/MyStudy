#include "base.h"
#include <windowsx.h>
#include "application.h"
#include "win32_helper.h"

namespace zee {
	static handle_t main_window_handle = nullptr;
	static handle_t instance_handle = nullptr;

	handle_t get_main_window_handle() { return main_window_handle; }
	handle_t get_instance_handle() { return instance_handle; }

	application app;
}//namespace zee 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("YESimpleRasterizer");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	zee::instance_handle = g_hInst;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
	hWnd = (HWND)zee::app.create(0, 0, 1280, 720);
	zee::main_window_handle = hWnd;
	zee::app.create_back_buffer();

	{
		zee::device_context dc;
		//bind.

	}
	{
		//func();

	}

	//hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
	//	100, 100, CW_USEDEFAULT, CW_USEDEFAULT,
	//	NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	using zee::app;
	switch (iMessage) {
	case WM_PAINT:
	{
		app.on_paint(iMessage, wParam, lParam);
		return 0;
	}
	break;

	case WM_SIZE:
	{
		zee::rect_t rect;
		GetClientRect(hWnd, &rect);
		app.width = width(rect);
		app.height = height(rect);

		app.create_back_buffer(app.width, app.height);
	}
	break;//case WM_SIZE:

	case WM_MOUSEMOVE:
	{
		if (app.b_is_down)
		{
			app.mouse_end = { GET_X_LPARAM(lParam) , GET_Y_LPARAM(lParam) };
			InvalidateRect(hWnd, NULL, FALSE);
		}
	}
	break;//case WM_MOUSEMOVE:

	case WM_LBUTTONDOWN:
	{
		app.b_is_down = true;
		app.mouse_end = app.mouse_start = { GET_X_LPARAM(lParam) , GET_Y_LPARAM(lParam) };
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;//case WM_LBUTTONDOWN:

	case WM_LBUTTONUP:
	{
		app.b_is_down = false;
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;//case WM_LBUTTONUP:

	case WM_MOUSEWHEEL:
	{
		auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		const int AddValue = 5;
		if (zDelta > 0) {
			app.pixel_size += AddValue;
		} else {
			if (app.pixel_size > AddValue) {
				app.pixel_size -= AddValue;
			}
		}

		if (app.pixel_size < 5) {
			app.pixel_size = 5;
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;//case WM_MOUSEWHEEL:

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			exit(0);
		}
		break;
	}
	break;//case WM_KEYDOWN:

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break; //case WM_DESTROY:

	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}