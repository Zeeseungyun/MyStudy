#include <windowsx.h>
#include "Rasterizing.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("YESimpleRasterizer");

ApplicationRasterizer Rasterizer;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

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
	
	hWnd = Rasterizer.CreateAppWindow(0, 0, 1280, 720);
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
	switch (iMessage) {
	case WM_PAINT:
		Rasterizer.OnPaint(iMessage, wParam, lParam);
		return 0;
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		Rasterizer.width = rect.right - rect.left;
		Rasterizer.height = rect.bottom - rect.top;
		Rasterizer.CreateBackBuffer(Rasterizer.width, Rasterizer.height);
		return 0;
	}

	case WM_MOUSEMOVE:
	{
		if (Rasterizer.b_is_down)
		{
			Rasterizer.mouse_end = { GET_X_LPARAM(lParam) , GET_Y_LPARAM(lParam) };
			InvalidateRect(hWnd, NULL, FALSE);
		}
	}
	return 0;

	case WM_LBUTTONDOWN:
	{
		Rasterizer.b_is_down = true;
		Rasterizer.mouse_end = Rasterizer.mouse_start = { GET_X_LPARAM(lParam) , GET_Y_LPARAM(lParam) };
		InvalidateRect(hWnd, NULL, FALSE);
	}
	return 0;

	case WM_LBUTTONUP:
	{
		Rasterizer.b_is_down = false;
		InvalidateRect(hWnd, NULL, FALSE);
	}
	return 0;

	case WM_MOUSEWHEEL:
	{
		auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		const int AddValue = 5;
		if (zDelta > 0) {
			Rasterizer.pixel_size += AddValue;
		} else {
			if (Rasterizer.pixel_size > AddValue) {
				Rasterizer.pixel_size -= AddValue;
			}
		}

		if (Rasterizer.pixel_size < 5) {
			Rasterizer.pixel_size = 5;
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}
	return 0;
	case WM_KEYDOWN:
		switch (wParam) 
		{
		case VK_ESCAPE:
			exit(0);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}