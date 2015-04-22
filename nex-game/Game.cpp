#include "stdafx.h"
#include <iostream>

#include "BitmapLoader.h"
#include "Render.h"
#include "Game.h"
#include "Sprite.h"
#include "Character.h"

Game::Game(Render* render)
{
	BM_INFOHEADER  bitmapInfoHeader;

	GameRenderer = render;
	GameState = GAME_STATE_INIT;
	GameTick = 0;

	LoadBitmapFile("spl.bmp", &bitmapInfoHeader, Splash, 320, 240);
	LoadBitmapFile("charmap.bmp", &bitmapInfoHeader, CharMap, 16, 1520);

}

Game::~Game()
{
	//
}

void Game::Wait(int ms)
{
	WaitTick = GetTickCount() + ms;
}

void Game::AddSprite(Sprite* sprite)
{
	SpriteList.push_back(sprite);
}

Sprite* Game::GetSprite(int index)
{
	return SpriteList.at(index);
}

void Game::DrawSplash()
{
	GameRenderer->BlockShiftBitmap(Splash, 0, 0, 320, 240, -1);
}

int Game::Update(Render* render)
{
	if (GetTickCount() < WaitTick)
		return 1;

	if (GameState == GAME_STATE_INIT)
	{
		GameTick++;

		if (GameTick < 10)
		{
			return 2;
		}
		else
		{
			render->Clear();
			GameState = GAME_STATE_ACTIVE;
		}
	}

	if (_kbhit())
	{
		char c = _getch();

		switch (c)
		{
		case 'w':printf("FORWARD");
		case 's':printf("BACKWARD");
		case 'a':printf("LEFT");
		case 'd':printf("RIGHT");
		}

		system("cls");
	}

	POINT p;
	GetCursorPos(&p);

	ScreenToClient(render->WindowHandle, &p);


	// Game rule code

	GameTick++;

	return 0;
}

void Game::DrawString(char* string, COLORREF colour)
{
	int length = strlen(string);
	int charpos = 0;
	int idxpos = 0;

	// Width (x) = length * 16, Height = 16
	COLORREF* bitmap = new COLORREF[(length * 16) * 16];

	if (bitmap == nullptr)
	{
		printf("ERROR: Could not allocate memory for DrawString bitmap, size: %d", (length * 16) * 16);
		return;
	}

	for (int i = 0; i < (length * 16) * 16; i++)
		bitmap[i] = RGB(255, 128, 0);

	int r, g, b;
	int u = (colour >> 0) & 0xFF;
	int v = (colour >> 8) & 0xFF;
	int w = (colour >> 16) & 0xFF;
	COLORREF newcolour;

	int pixel = 0;

	for (int character = 0; character < length; ++character)
	{
		charpos = (string[character] - ' ') * 16 * 16;
		// memcpy(&bitmap[i * 16 * 16], &CharMap[charpos], 16 * 16 * 4);

		pixel = 0;

		for (int x = 0; x < 16; ++x)
		{
			for (int y = 0; y < 16; ++y)
			{
				r = (((CharMap[charpos + pixel] >> 0) & 0xFF) + 255 - u);
				g = (((CharMap[charpos + pixel] >> 8) & 0xFF) + 255 - v);
				b = (((CharMap[charpos + pixel] >> 16) & 0xFF) + 255 - w);

				idxpos = 16 * (x * length) + y + 16 * character;// ((pixel % 16) + (pixel / 16)) * 16 * length + 16 * character;// pixel + (character * 16 * 16);

				if (idxpos > (length * 16) * 16)
				{
					printf("ERROR:");
				}

				bitmap[idxpos] = RGB(r, g, b);;

				pixel++;
			}
		}

		for (int pixel = 0; pixel < 16 * 16; ++pixel)
		{
		}
	}

	GameRenderer->BlockShiftBitmap(bitmap, 160 - ((length * 16) / 2), 112, length * 16, 16, 0xFFFFFF);

	delete[] bitmap;
}
