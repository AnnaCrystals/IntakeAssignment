#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL_scancode.h>
#include "bottle.h"
#include "player.h"
#include "map.h"


namespace Tmpl8
{
	Game::Game()
	{
		myBottle = new Bottle;


	}

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
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXabX",
		 "lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXlc lc lc lc lc abXabXabXabXabX",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc abXabXabXabXabXabXabXabXabXabX",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc abXabXabXabXabXabXabXabXabXabX",
	};

	void Game::SetTarget(Surface* surface)
	{
		screen = surface;
		myPlayer = new Player(map, screen);
		myBottle->SetPlayer(myPlayer);
	}

	void Game::Init() 
	{
		Map::FolderRead();
	}


	void Game::Shutdown()
	{
		delete myBottle;
		delete myPlayer;
	}

	//Drawing of a singular tile
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + tx * 33 + (ty * 33) * 595;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++, src += tiles.GetWidth(), dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}



	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;

		myPlayer->screen = screen;

		myPlayer->HandleCollision(deltaTime);
		myBottle->HandleHit(myPlayer->playerPosition, myPlayer->screen, myBottle);

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


		

		myBottle->Draw(screen, myBottle->bottlePosition);
		screen->Box(myBottle->bottlePosition.x, myBottle->bottlePosition.y, myBottle->bottlePosition.x + myBottle->bottleSprite->GetWidth(), myBottle->bottlePosition.y + myBottle->bottleSprite->GetHeight(), 0xffff00);
		
		myPlayer->playerSprite->Draw(screen, static_cast<int> (myPlayer->playerPosition.x), static_cast<int>(myPlayer->playerPosition.y));
		screen->Box(myPlayer->playerVelocity.x + myPlayer->playerPosition.x, myPlayer->playerVelocity.y + myPlayer->playerPosition.y, myPlayer->playerVelocity.x + myPlayer->playerSprite->GetWidth() + myPlayer->playerPosition.x, myPlayer->playerVelocity.y + static_cast<float> (myPlayer->playerSprite->GetHeight()) + myPlayer->playerPosition.y, 0xffff00);
	}
};