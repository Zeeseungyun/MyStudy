#include "Rasterizing.h"

void ApplicationRasterizer::DrawLine_DDA(POINT start_pt, POINT end_pt, COLORREF color)
{
	lines.emplace_back();

	float start_x = start_pt.x / pixel_size; float start_y = start_pt.y / pixel_size;
	float end_x = end_pt.x / pixel_size; float end_y = end_pt.y / pixel_size;
	float dx = end_x - start_x;
	float dy = end_y - start_y;
	float addx = 0.0f;
	float addy = 0.0f;
	int count = 0;
	addx = dx < 0 ? -1.0f : 1.0f;
	addy = dy < 0 ? -1.0f : 1.0f;

	if (dx == 0.0f) {
		addx = 0.0f;
		count = (int)abs(dy);
	} else if (dy == 0.0f) {
		addy = 0.0f;
		count = (int)abs(dx);
	} else {
		float adx = abs(dx);
		float ady = abs(dy);

		if (adx > ady)
		{
			count = (int)abs(dx);
			addy = dy / abs(dx);
		}
		else
		{
			count = (int)abs(dy);
			addx = dx / abs(dy);
		}
	}
	
	for(int i = 0 ; i <= count; ++i) {
		SetPixel({ (int)start_x , (int)start_y }, color);
		start_x += addx;
		start_y += addy;
	}
}

void ApplicationRasterizer::BeginPlay()
{
	lines.clear();
	DrawLine_DDA({ 100, 200 }, { 500, 100 }, RGB(255, 0, 0));
	DrawLine_DDA({ 500, 0 }  , { 0, 500 }, RGB(0, 0, 255));
	DrawLine_DDA({ 500, 500 }, { 0, 0 }, RGB(0, 255, 0));
	if (b_is_down)
	{
		DrawLine_DDA(mouse_start, mouse_end, RGB(230,230,230));
	}
}

void ApplicationRasterizer::DrawLine_Bresenhem(POINT start_pt, POINT end_pt, COLORREF color)
{
	lines.emplace_back();
	int start_x = start_pt.x / pixel_size; 
	int start_y = start_pt.y / pixel_size;
	int end_x = end_pt.x / pixel_size; 
	int end_y = end_pt.y / pixel_size;

}