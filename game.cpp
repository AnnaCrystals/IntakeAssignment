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
	char map[16][76] = {
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

	/*void Game::KeyDown(int key) {
		switch (key) {
		case SDL_SCANCODE_SPACE:
			ballVelocity.y = -10.0f;
			break;
		}
	}

	void Game::KeyUp(int key) {
		switch (key) {
		case SDL_SCANCODE_SPACE:
			ballVelocity.y = 0.0f;
			break;
		}
	}*/

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
		float nx = ballPosition.x, ny = ballPosition.y;

		if (GetAsyncKeyState(VK_SPACE)) ny = ny - 10.0f;
		if (GetAsyncKeyState(VK_LEFT)) nx--;
		if (GetAsyncKeyState(VK_RIGHT)) nx++;
	
		if (CheckPos(nx, ny) && CheckPos(nx + 50, ny + 50) &&
			CheckPos(nx + 50, ny) && CheckPos(nx, ny + 50))
		{
			ballPosition.x = nx, ballPosition.y = ny;
		}
		else
		{
			//Player bottom hits obstacle
			if (!CheckPos(nx, ny + 50) && !CheckPos(nx + 50, ny + 50) && CheckPos(nx, ny) && CheckPos(nx + 50, ny) ||
				!CheckPos(nx + 49, ny + 50) && CheckPos(nx + 1, ny) && CheckPos(nx + 49, ny) ||
				!CheckPos(nx + 1, ny + 50) && CheckPos(nx + 1, ny) && CheckPos(nx + 49, ny)) 
			{
				std::cout << "Set gravity to 0" << std::endl;
				gravity = 0.0f;
				ballPosition.x = nx, ballPosition.y = ny;
			}			
		}

		
		screen->Clear(0);


		//Altering the ballposition
		ballPosition += ballVelocity * ballSpeed * deltaTime;


		//Checking if the ball is in the air
		if (ballPosition.y + ballSprite->GetHeight() < screen->GetHeight())
		{
			ballPosition.y += gravity * deltaTime;
			gravity += 1.0f;
		}


		//Checking if the ball is on ground level
		if (ballPosition.y + ballSprite->GetHeight() > screen->GetHeight())
		{
			ballPosition.y = screen->GetHeight() - ballSprite->GetHeight();
			gravity = 0.0f;
		}


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