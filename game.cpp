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


	class Bottle
	{
	public:
		Bottle()
		{
			bottlePosition.x = ScreenWidth / 2.0f;
			bottlePosition.y = ScreenHeight - 300.0f;
			bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);
		}

		Sprite* bottleSprite;
		vec2 bottlePosition;
		const int bottleHeight = 50.0f;
		const int bottleWidth = 50.0f;

		void Bottle::Spawn(Surface* gameScreen, vec2& ballPosition, bool& hitSpawn)
		{

			int bottleMinX = static_cast<int>(ballPosition.x / bottleWidth);
			int bottleMinY = static_cast<int>(ballPosition.y / bottleHeight);
			int bottleMaxX = static_cast<int>((ballPosition.x + 50) / bottleWidth);
			int bottleMaxY = static_cast<int>((ballPosition.y + 50) / bottleHeight);

			if (hitSpawn) {
				//if (map[bottleMinY][bottleMinX * 3 + 2] == 'S' && map[bottleMaxY][bottleMinX * 3 + 2] != 'S') {
				bottleSprite->Draw(gameScreen, static_cast<int> (bottlePosition.x), static_cast<int>(bottlePosition.y));
				//}
			}
		}
		
	};




	void Game::Init()
	{
		ballSprite = new Sprite(new Surface("assets/ball.png"), 1);
		ballSize.x = ballSprite->GetWidth() / 2.0f;
		ballSize.y = ballSprite->GetHeight() / 2.0f;
		ballPosition.x = ScreenWidth / 2.0f;
		ballPosition.y = ScreenHeight - ballSprite->GetHeight();

		/*bottlePosition.x = ScreenWidth / 2.0f;
		bottlePosition.y = ScreenHeight - 300.0f;
		bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);*/
		
	}
	void Game::Shutdown() {}

	//The tilemap
	Surface tiles("assets/mediaval.png");
	const int numRows = 16;
	const int numColums = 76;
	char map[numRows][numColums] = {
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lcSlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lcSlc lc lc",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lcSlc lc lc lc lc lc lc abXabXabXabXab",
		 "lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXlc lc lc lc lc abXabXabXabXab",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lcSlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lcSlc lc lc",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXab",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXab",
	};

	



	//Drawing of a singular tile
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		//Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
		Pixel* src = tiles.GetBuffer()  + tx * 33 + (ty * 33) * 595;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++, src += tiles.GetWidth(), dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}


	void Game::Tick(float deltaTime)
	{
		Bottle myBottle;
		bool hitSpawn = true;
		deltaTime /= 1000.0f;

		prevBallPosition.y = ballPosition.y;
		prevBallPosition.x = ballPosition.x;
		prevGravity = gravity;

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
			gravity += 1.5f;
			std::cout << gravity << std::endl;
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
			//gravity = prevGravity;
		}

		if (map[tileMinY][tileMaxX * 3 + 2] == 'X' && map[tileMaxY][tileMaxX * 3 + 2] != 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
			//gravity = prevGravity;
		}

		if (map[tileMaxY][tileMaxX * 3 + 2] == 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
			//gravity = prevGravity;
		}

		if (map[tileMaxY][tileMinX * 3 + 2] == 'X') {
			ballPosition.x = prevBallPosition.x;
			ballPosition.y = prevBallPosition.y;
			gravity = 0.0f;
			//gravity = prevGravity;
		}

		if (ballPosition.y + ballSprite->GetHeight() > screen->GetHeight())
		{
			ballPosition.y = screen->GetHeight() - ballSprite->GetHeight();
			gravity = 0.0f;
		}

		if (map[tileMinY][tileMinX * 3 + 2] == 'S' || map[tileMaxY][tileMinX * 3 + 2] != 'S') {
			hitSpawn = false;
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

		myBottle.Spawn(screen, ballPosition, hitSpawn);
		//bottleSprite->Draw(screen, static_cast<int> (bottlePosition.x), static_cast<int>(bottlePosition.y));
		ballSprite->Draw(screen, static_cast<int> (ballPosition.x), static_cast<int>(ballPosition.y));

		screen->Box(ballPosition.x, ballPosition.y, ballPosition.x + ballSprite->GetWidth(), ballPosition.y + ballSprite->GetHeight(), 0xffff00);
	}
};