#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL_scancode.h>


namespace Tmpl8
{

	void Game::Init()
	{
		ballSprite = new Sprite(new Surface("assets/ball.png"), 1);
		ballSize.x = ballSprite->GetWidth() / 2.0f;
		ballSize.y = ballSprite->GetHeight() / 2.0f;
		ballPosition.x = ScreenWidth / 2.0f;
		ballPosition.y = ScreenHeight - ballSprite->GetHeight();
		
	}
	void Game::Shutdown() {}

	//The tilemap
	Surface tiles("assets/nc2tiles.png");
	const int numRows = 16;
	const int numColums = 76;
	char map[numRows][numColums] = {
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc fbXfbXfbXfbX",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc fbXfbXfbXfbX",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc fbXfbXfbXfbXfbXkc kc kc kc lc kc kc kc kc ",
		 "kc kc kc lc lc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc kc kc kc kc ",
		 "fbXfbXfbXfbXlc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc fbXfbXfbXfbX",
		 "fbXfbXfbXfbXlc lc kc kc kc kc kc kc kc lc lc lc kc kc kc kc lc fbXfbXfbXfbX",
	};

	//Drawing of a singular tile
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++, src += 595, dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}


	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;

		prevBallPosition.y = ballPosition.y;
		prevBallPosition.x = ballPosition.x;

		if (GetAsyncKeyState(VK_SPACE)) ballPosition.y = ballPosition.y - 10.0f;
		if (GetAsyncKeyState(VK_LEFT)) ballPosition.x--;
		if (GetAsyncKeyState(VK_RIGHT)) ballPosition.x++;
		if (GetAsyncKeyState(VK_DOWN)) ballPosition.y++;
		if (GetAsyncKeyState(VK_UP)) ballPosition.y--;

		ballPosition.y += ballVelocity.y * deltaTime;
		ballPosition.x += ballVelocity.x * deltaTime;

		// Apply gravity
		if (ballPosition.y + ballSprite->GetHeight() < screen->GetHeight()) {
			ballPosition.y += gravity * deltaTime;
			gravity += 1.0f;
		}

		int tileMinX = static_cast<int>(ballPosition.x / tileWidth);
		int tileMinY = static_cast<int>(ballPosition.y / tileHeight);
		int tileMaxX = static_cast<int>((ballPosition.x + 50) / tileWidth);
		int tileMaxY = static_cast<int>((ballPosition.y + 50) / tileHeight);

		// Check for collisions and reset position if necessary
		if (map[tileMinY][tileMinX * 3 + 2] == 'X' && map[tileMaxY][tileMinX * 3 + 2] != 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
		}

		if (map[tileMinY][tileMaxX * 3 + 2] == 'X' && map[tileMaxY][tileMaxX * 3 + 2] != 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
		}

		if (map[tileMaxY][tileMaxX * 3 + 2] == 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
		}

		if (map[tileMaxY][tileMinX * 3 + 2] == 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
		}

		screen->Clear(0);


		//Drawing the tilemap, a grid of 16x25 tiles 
		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				int tx = map[y][x * 3] - 'a';
				int ty = map[y][x * 3 + 1] - 'a';
				DrawTile(tx, ty, screen, x * 32, y * 32);
			}
		}

		ballSprite->Draw(screen, static_cast<int> (ballPosition.x), static_cast<int>(ballPosition.y));

		screen->Box(ballPosition.x, ballPosition.y, ballPosition.x + ballSprite->GetWidth(), ballPosition.y + ballSprite->GetHeight(), 0xffff00);
	}
};