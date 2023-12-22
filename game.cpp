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
		ballSize.x = ballSprite->GetWidth() / 2.0f;//IMPORTANT
		ballSize.y = ballSprite->GetHeight() / 2.0f;//IMPORTANT
		ballPosition.x = ScreenWidth / 2.0f;//IMPORTANT
		ballPosition.y = ScreenHeight; //IMPORTANT


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


	//Check for an X in the tilemap
	bool CheckPos(int x, int y)
	{
		int tx = x / 32, ty = y / 32;
		return map[ty][tx * 3 + 2] != 'X';

	}

	
	//Drawing of a singular tile
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++, src += 595, dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}

	static bool AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
	{
		return aX < bX + bWidth - 1 &&
			aX + aWidth - 1>= bX &&
			aY <= bY + bHeight - 1 &&
			aY + aHeight - 1 >= bY;
	}

	const int tileWidth = 32;
	const int tileHeight = 32;

	//Watch this video for explanation for collision
//https://www.youtube.com/watch?v=SoSHVoIZYbY
//I have to figure out how to get the coordinates of a tile

//MAYBE this

//for (int y = __; y < ___ + 2 * tile size;;;;)
//	for (int x = ___; x < ___ + 2 * tile size;;;;)
//		checkCollision(x, y, somethingsomethign)

	void Game::Tick(float deltaTime)
	{


		
		deltaTime /= 1000.0f;

		// ... (previous code)

		int tileMinX = static_cast<int>(ballPosition.x / tileWidth);
		int tileMinY = static_cast<int>(ballPosition.y / tileHeight);
		int tileMaxX = static_cast<int>((ballPosition.x + 50) / tileWidth);
		int tileMaxY = static_cast<int>((ballPosition.y + 50) / tileHeight);

		prevBallPosition.y = ballPosition.y;
		prevBallPosition.x = ballPosition.x;


		if (GetAsyncKeyState(VK_SPACE)) ballPosition.y = ballPosition.y - 10.0f;
		if (GetAsyncKeyState(VK_LEFT)) ballPosition.x--;
		if (GetAsyncKeyState(VK_RIGHT)) ballPosition.x++;
		if (GetAsyncKeyState(VK_DOWN)) ballPosition.y++;
		if (GetAsyncKeyState(VK_UP)) ballPosition.y--;

		ballPosition.y += ballVelocity.y * deltaTime;
		ballPosition.x += ballVelocity.x * deltaTime;

		// Check for collisions and reset position if necessary
		if (map[tileMinY][tileMinX * 3 + 2] == 'X' || map[tileMinY][tileMaxX * 3 + 2] == 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
		}
		
		if (map[tileMaxY][tileMinX * 3 + 2] == 'X' || map[tileMaxY][tileMaxX * 3 + 2] == 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
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