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
			bottlePosition.x = ScreenWidth / 2.0f + 100.0f;
			bottlePosition.y = ScreenHeight - 50.0f;
			bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);

		}
		

		Sprite* bottleSprite;
		vec2 bottlePosition;
		const int bottleHeight = 50.0f;
		const int bottleWidth = 50.0f;

		static bool AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
		{
			return aX < bX + bWidth &&
				aX + aWidth >= bX &&
				aY <= bY + bHeight &&
				aY + aHeight >= bY;
		}

		void Spawn(Surface* gameScreen, vec2& ballPosition)
		{
			bottleSprite->Draw(gameScreen, static_cast<int>(bottlePosition.x), static_cast<int>(bottlePosition.y));
		}

		void DeSpawn(int number)
		{

			if (number == 1) {
				delete bottleSprite;
				bottleSprite = nullptr;
			}
		}

		void HandleHit(vec2& ballPosition, vec2& ballSize){

			int number;
			float playerBallPositionX = ballPosition.x;
			float playerBallPositionY = ballPosition.y;


			float positionOneX = ScreenWidth / 2.0f + 100.0f;
			float positionOneY = ScreenHeight - ballSize.y;

			float positionTwoX = ScreenWidth / 2.0f - 100.0f;
			float positionTwoY = ScreenHeight - ballSize.y;

			float positionThreeX = ScreenWidth / 2.0f + 200.0f;
			float positionThreeY = ScreenHeight - ballSize.y;

			float positionFourX = ScreenWidth / 2.0f - 200.0f;
			float positionFourY = ScreenHeight - ballSize.y;

			float positionFiveX = ScreenWidth / 2.0f + 300.0f;
			float positionFiveY = ScreenHeight - ballSize.y;

			if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionOneX, positionOneY, 50, 50))
			{
				number = 1;
				DeSpawn(number);
			}
			if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionTwoX, positionTwoY, 50, 50))
			{
				number = 2;
				DeSpawn(number);
			}
			if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionThreeX, positionThreeY, 50, 50))
			{
				number = 3;
				DeSpawn(number);
			}
			if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionFourX, positionFourY, 50, 50))
			{
				number = 4;
				DeSpawn(number);
			}
			if (AABB(playerBallPositionX, playerBallPositionY, 50, 50,
				positionFiveX, positionFiveY, 50, 50))
			{
				number = 5;
				DeSpawn(number);
			}

		}
	};



	class Player
	{
		public:Player(char(*gameMap)[76], Surface* gameScreen) : screen(gameScreen), deltaTime(0.0f), map(gameMap)
		{
			ballSprite = new Sprite(new Surface("assets/ball.png"), 1);
			ballSize.x = ballSprite->GetWidth() / 2.0f;
			ballSize.y = ballSprite->GetHeight() / 2.0f;
			ballPosition.x = ScreenWidth / 2.0f;
			ballPosition.y = ScreenHeight - ballSprite->GetHeight();
		}
			  Sprite* ballSprite;
			  vec2 ballPosition;
			  vec2 ballSize;
			  float gravity = 0.0f;
			  vec2 prevBallPosition{ ballPosition.x, ballPosition.y };
			  Surface* screen;

			  float deltaTime;
			  const int tileWidth = 32;
			  const int tileHeight = 32;
			  float prevGravity;
			  vec2 ballVelocity{ 0, 0 };

		
			  void Player::UpdatePosition()
			  {
				  if (GetAsyncKeyState(VK_SPACE)) ballPosition.y -= 10.0f;
				  if (GetAsyncKeyState(VK_LEFT)) ballPosition.x--;
				  if (GetAsyncKeyState(VK_RIGHT)) ballPosition.x++;
				  if (GetAsyncKeyState(VK_DOWN)) ballPosition.y++;
				  if (GetAsyncKeyState(VK_UP)) ballPosition.y--;

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
					  ballPosition.y = prevBallPosition.y - 1.0f;
					  gravity = 0.0f;
				  }
				  if (map[tileMaxY][tileMinX * 3 + 2] == 'X' && map[tileNew][tileMinX * 3 + 2] != 'X') {
					  ballPosition.x = prevBallPosition.x;
					  ballPosition.y = prevBallPosition.y - 1.0f;
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

				  if (ballPosition.y + ballSprite->GetHeight() > screen->GetHeight())
				  {
					  ballPosition.y = screen->GetHeight() - ballSprite->GetHeight();
					  gravity = 0.0f;
				  }
			  }

			  void Player::HandleCollision()
			  {
				  prevBallPosition.y = ballPosition.y;
				  prevBallPosition.x = ballPosition.x;
				  prevGravity = gravity;

				  UpdatePosition();
				  CheckCollision();
			  }
	private:
		char(*map)[76];
	};


	void Game::Init(){}


	void Game::Shutdown() {}









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
		
		Player myPlayer(map, screen);
		Bottle myBottle;

		bool hitObject = false;

		deltaTime /= 1000.0f;

		myPlayer.screen = screen;
		myPlayer.deltaTime = deltaTime;
		myPlayer.HandleCollision();





		myBottle.HandleHit(myPlayer.ballPosition, myPlayer.ballSize);


		



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





		myBottle.Spawn(screen, myPlayer.ballPosition);
		myPlayer.ballSprite->Draw(screen, static_cast<int> (myPlayer.ballPosition.x), static_cast<int>(myPlayer.ballPosition.y));
		//screen->Box(myPlayer.ballPosition.x, myPlayer.ballPosition.y, myPlayer.ballPosition.x + myPlayer.ballSprite->GetWidth(), myPlayer.ballPosition.y + myPlayer.ballSprite->GetHeight(), 0xffff00);
	}
};