#pragma once
#include "stdafx.h"


const int CONSOLE_SIZE_X = 80;
const int CONSOLE_SIZE_Y = 30;
const int SCREEN_SIZE_X = 320;
const int SCREEN_SIZE_Y = 240;
const int FBUFFER_SIZE = (SCREEN_SIZE_X * SCREEN_SIZE_Y);

class Render
{
public:
	Render();
	~Render();
	void SetFrameBufferPixel(int x, int y, COLORREF colour);
	void BlockShiftBitmap(COLORREF* arr, int x, int y, int width, int height, COLORREF trans); // arr length should be width * height
	void Clear();
	void Update();
	void ClientToFrame(POINT* point);

	HWND WindowHandle;

private:
	COLORREF * FrameBuffer;
};
