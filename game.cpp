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
		background = new Surface("assets/background.png");
	
	}

	Surface tiles("assets/mediaval.png");
	


	void Game::Init()
	{
		myMap.LoadMap("assets/tile/tilemap_Tilelaag_1.csv", 0);
		collisionMap.LoadMap("assets/tile/tilemap_CollisionLaag.csv", 0);

	}

	void Game::SetTarget(Surface* surface)
	{
		screen = surface;
		myPlayer = new Player(&collisionMap, screen);
		myBottle->SetPlayer(myPlayer);
	}

	


	void Game::Shutdown()
	{
		delete myBottle;
		delete myPlayer;
	}

	//Drawing of a singular tile
	void DrawTile(int value, Surface* screen, int x, int y)
	{
		int tilesetWidth = tiles.GetWidth() / 32;
		int tileWidth = 32;
		int tileHeight = 32;


		int srcX = (value % tilesetWidth) * tileWidth;
		int srcY = (value / tilesetWidth) * tileHeight;

		Pixel* src = tiles.GetBuffer() + srcX + srcY * tiles.GetWidth();
		Pixel* dst = screen->GetBuffer() + x + y * 800;

		for (int i = 0; i < tileHeight; i++, src += tiles.GetWidth(), dst += 800)
		{
			for (int j = 0; j < tileWidth; j++)
			{
				dst[j] = src[j];
			}
		}
	 }

	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;
		
		myPlayer->screen = screen;

		myPlayer->HandleCollision(deltaTime);
		myBottle->HandleHit(myPlayer->playerPosition, myPlayer->screen, myBottle);


		screen->Clear(0);
		

		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				int value = myMap.map[0][y][x];
				DrawTile(value, screen, x * 32, y * 32);
			}
		}
		//screen->Resize(background);

		myBottle->Draw(screen, myBottle->bottlePosition);
		screen->Box(myBottle->bottlePosition.x, myBottle->bottlePosition.y, myBottle->bottlePosition.x + myBottle->bottleSprite->GetWidth(), myBottle->bottlePosition.y + myBottle->bottleSprite->GetHeight(), 0xffff00);
		
		myPlayer->playerSprite->Draw(screen, static_cast<int> (myPlayer->playerPosition.x), static_cast<int>(myPlayer->playerPosition.y));
		//myPlayer->playerSpriteIdle->Draw(screen, static_cast<int> (myPlayer->playerPosition.x), static_cast<int>(myPlayer->playerPosition.y));
		//screen->Box(myPlayer->playerVelocity.x + myPlayer->playerPosition.x, myPlayer->playerVelocity.y + myPlayer->playerPosition.y, myPlayer->playerVelocity.x + myPlayer->playerSprite->GetWidth() + myPlayer->playerPosition.x, myPlayer->playerVelocity.y + static_cast<float> (myPlayer->playerSprite->GetHeight()) + myPlayer->playerPosition.y, 0xffff00);
		screen->Box(myPlayer->playerPosition.x, myPlayer->playerPosition.y, myPlayer->playerSprite->GetWidth() + myPlayer->playerPosition.x,  static_cast<float> (myPlayer->playerSprite->GetHeight()) + myPlayer->playerPosition.y, 0xffff00);
	}
};