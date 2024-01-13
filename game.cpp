#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
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
			/*bottlePosition.x = ScreenWidth / 2.0f + 100.0f;
			bottlePosition.y = ScreenHeight - 50.0f;*/

			bottlePosition.x = 200.0f;
			bottlePosition.y = 100.0f;
			bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);

		}
		

		Sprite* bottleSprite;
		vec2 bottlePosition;
		Bottle* newBottle;

	

		const int bottleHeight = 50.0f;
		const int bottleWidth = 50.0f;
		bool despawned = false;

		static bool AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
		{
			return aX < bX + bWidth &&
				aX + aWidth >= bX &&
				aY <= bY + bHeight &&
				aY + aHeight >= bY;
		}

		static int randomNumber ()
		{
			srand(static_cast<unsigned int>(time(0))); //seed random number generator

			int randomNumber = rand();
			int number = (randomNumber % 5) + 1;

			return number;
		}

		static vec2 setSpawnPosition()
		{
			vec2 validSpawnPositions[5] = {
				vec2(200.0f, 100.0f),
				vec2(200.0f, 175.0f),
				vec2(200.0f, 250.0f),
				vec2(200.0f, 325.0f),
				vec2(200.0f, 400.0f)
			};

			int number = randomNumber();

			switch (number) 
			{
			case 1:
				return validSpawnPositions[0];

				break;
			case 2:
				return validSpawnPositions[1];

				break;
			case 3:
				return validSpawnPositions[2];

				break;
			case 4:
				return validSpawnPositions[3];

				break;
			case 5:
				return validSpawnPositions[4];
				break;

			}
			
		}

		void Bottle::Spawn(Surface* gameScreen, vec2 bottlePosition)
		{
			if (bottleSprite) {
				bottleSprite->Draw(gameScreen, static_cast<int>(bottlePosition.x), static_cast<int>(bottlePosition.y));
			}
		}

		void Bottle::DeSpawn(Surface* screen)
		{
				std::cout << "hit" << std::endl;

				//delete bottleSprite;
				//bottleSprite = nullptr;
		
				bottlePosition = setSpawnPosition();

				Spawn(screen, bottlePosition);

				std::cout << bottlePosition.x << std::endl;
				std::cout << bottlePosition.y << std::endl;
			
		}

		void Bottle::HandleHit(vec2& ballPosition, vec2& ballSize, Surface* screen, Bottle* myBottle){

			int number;
			float playerBallPositionX = ballPosition.x;
			float playerBallPositionY = ballPosition.y;


			/*float positionOneX = ScreenWidth / 2.0f + 100.0f;
			float positionOneY = ScreenHeight - ballSize.y;

			float positionTwoX = ScreenWidth / 2.0f - 100.0f;
			float positionTwoY = ScreenHeight - ballSize.y;

			float positionThreeX = ScreenWidth / 2.0f + 200.0f;
			float positionThreeY = ScreenHeight - ballSize.y;

			float positionFourX = ScreenWidth / 2.0f - 200.0f;
			float positionFourY = ScreenHeight - ballSize.y;

			float positionFiveX = ScreenWidth / 2.0f + 300.0f;
			float positionFiveY = ScreenHeight - ballSize.y;*/
			///////////////////////////////////////////////////
			float positionOneX = 200.0f;
			float positionOneY = 100.0f;

			float positionTwoX = 200.0f;
			float positionTwoY = 175.0f;

			float positionThreeX = 200.0f;
			float positionThreeY = 250.0f;

			float positionFourX = 200.0f;
			float positionFourY = 325.0f;

			float positionFiveX = 200.0f;
			float positionFiveY = 400.0f;

			if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionOneX, positionOneY, 50, 50)  && bottlePosition.x==positionOneX && bottlePosition.y==positionOneY)
			{
				DeSpawn(screen);
			}
			else if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionTwoX, positionTwoY, 50, 50) && bottlePosition.x == positionTwoX && bottlePosition.y == positionTwoY)
			{
				DeSpawn(screen);
			}
			else if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionThreeX, positionThreeY, 50, 50) && bottlePosition.x == positionThreeX && bottlePosition.y == positionThreeY)
			{

				DeSpawn(screen);
			}
			else if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionFourX, positionFourY, 50, 50) && bottlePosition.x == positionFourX && bottlePosition.y == positionFourY)
			{
				DeSpawn(screen);
			}
			else if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionFiveX, positionFiveY, 50, 50) && bottlePosition.x == positionFiveX && bottlePosition.y == positionFiveY)
			{
				DeSpawn(screen);
			}

		}
	};



	class Player
	{
		public:Player(char(*gameMap)[76], Surface* screen) : screen(screen), map(gameMap)
		{
			ballSprite = new Sprite(new Surface("assets/ball.png"), 1);
			ballSize.x = ballSprite->GetWidth() / 2.0f;
			ballSize.y = ballSprite->GetHeight() / 2.0f;
			ballPosition.x = ScreenWidth / 2.0f;
			ballPosition.y = ScreenHeight - ballSprite->GetHeight();
		}

			  Sprite* ballSprite;
			  Surface* screen;

			  vec2 ballPosition;
			  vec2 prevBallPosition{ ballPosition.x, ballPosition.y };
			  vec2 ballSize;
			  vec2 ballVelocity{ 0, 0 };

			  float gravity = 0.0f;
			  float prevGravity;
			  
			  const int tileWidth = 32;
			  const int tileHeight = 32;
			  float ballSpeed = 120.0f;
			  

			  void Player::UpdatePosition(float deltaTime)
			  {
				  if (GetAsyncKeyState(VK_SPACE)) ballPosition.y -= 10.0f;
				  if (GetAsyncKeyState(VK_LEFT)) ballPosition.x-= ballSpeed * deltaTime;
				  if (GetAsyncKeyState(VK_RIGHT)) ballPosition.x+= ballSpeed * deltaTime;
				  if (GetAsyncKeyState(VK_DOWN)) ballPosition.y+= ballSpeed * deltaTime;
				  if (GetAsyncKeyState(VK_UP)) ballPosition.y-= ballSpeed * deltaTime;

				  ballPosition.y += ballVelocity.y * gravity * deltaTime;
				  ballPosition.x += ballVelocity.x * gravity * deltaTime;

				  if (ballPosition.y + ballSprite->GetHeight() < screen->GetHeight()) {
					  ballPosition.y += gravity * deltaTime;
					  gravity += 1.5f;
				  }
			  }


			  void Player ::CheckCollision()
			  {
				  int tileMinX = static_cast<int>(ballPosition.x / tileWidth);
				  int tileMinY = static_cast<int>(ballPosition.y / tileHeight);
				  int tileMaxX = static_cast<int>((ballPosition.x + 50) / tileWidth);
				  int tileMaxY = static_cast<int>((ballPosition.y + 50) / tileHeight);
				  int tileNew = static_cast<int>((ballPosition.y + 49) / tileHeight);

				  if (ballPosition.y + ballSprite->GetHeight() > screen->GetHeight())
				  {
					  ballPosition.y = screen->GetHeight() - ballSprite->GetHeight();
					  gravity = 0.0f;
				  }
				  // Check for collisions and reset position if necessary
				  if (map[tileMinY][tileMinX * 3 + 2] == 'X' && map[tileMaxY][tileMinX * 3 + 2] != 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y;
				  }
				  if (map[tileMinY][tileMaxX * 3 + 2] == 'X' && map[tileMaxY][tileMaxX * 3 + 2] != 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y;
				  }


				  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X' && map[tileNew][tileMaxX * 3 + 2] != 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y - 0.1f;
					  gravity = 0.0f;
				  }
				  if (map[tileMaxY][tileMinX * 3 + 2] == 'X' && map[tileNew][tileMinX * 3 + 2] != 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y - 0.1f;
					  gravity = 0.0f;

				  }
				  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X' && map[tileNew][tileMaxX * 3 + 2] == 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y;
					  gravity = 0.0f;
				  }
				  if (map[tileMaxY][tileMinX * 3 + 2] == 'X' && map[tileNew][tileMinX * 3 + 2] == 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y;
					  gravity = 0.0f;
				  }



			  }

			  void Player::HandleCollision(float deltaTime)
			  {
				  prevBallPosition.y = ballPosition.y;
				  prevBallPosition.x = ballPosition.x;
				  prevGravity = gravity;

				  UpdatePosition(deltaTime);
				  CheckCollision();
			  }
	private:
		char(*map)[76];
	};


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
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXabX",
		 "abXabXabXabXlc lc lc lc lc lc lc lc lc lc lc lc lc lc lc lc abXabXabXabXabX",
	};

	void Game::SetTarget(Surface* surface)
	{

		screen = surface; 
		myPlayer = new Player(map, screen);
	}

	void Game::Init(){}


	void Game::Shutdown() 
	{
		delete myBottle;
		delete myPlayer;
	}

	//Drawing of a singular tile
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		//Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
		Pixel* src = tiles.GetBuffer() + tx * 33 + (ty * 33) * 595;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++, src += tiles.GetWidth(), dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}

	

	void Game::Tick(float deltaTime)
	{
		int number;
		bool hitObject = false;

		deltaTime /= 1000.0f;

		myPlayer->screen = screen;

		myPlayer->HandleCollision(deltaTime);
		myBottle->HandleHit(myPlayer->ballPosition, myPlayer->ballSize, myPlayer->screen, myBottle);
		
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

		myBottle->Spawn(screen, myBottle->bottlePosition);
		myPlayer->ballSprite->Draw(screen, static_cast<int> (myPlayer->ballPosition.x), static_cast<int>(myPlayer->ballPosition.y));
		//screen->Box(myPlayer.ballPosition.x, myPlayer.ballPosition.y, myPlayer.ballPosition.x + myPlayer.ballSprite->GetWidth(), myPlayer.ballPosition.y + myPlayer.ballSprite->GetHeight(), 0xffff00);
	}
};