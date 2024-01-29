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



		const float bottleHeight = 50.0f;
		const float bottleWidth = 50.0f;
		bool despawned = false;
		int score = 0;

		static bool AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
		{
			return aX < bX + bWidth &&
				aX + aWidth >= bX &&
				aY <= bY + bHeight &&
				aY + aHeight >= bY;
		}

		static int randomNumber()
		{
			static int previousNumber = 0;

			srand(static_cast<unsigned int>(time(0)));

			int newNumber;

			do
			{
				int randomNumber = rand();
				newNumber = (randomNumber % 5) + 1;
			} while (newNumber == previousNumber);

			std::cout << previousNumber << std::endl;
			previousNumber = newNumber;
			return newNumber;
		}

		static vec2 setDrawPosition()
		{
			vec2 validDrawPositions[5] = {
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
				return validDrawPositions[0];

				break;
			case 2:
				return validDrawPositions[1];

				break;
			case 3:
				return validDrawPositions[2];

				break;
			case 4:
				return validDrawPositions[3];

				break;
			case 5:
				return validDrawPositions[4];
				break;


			}


		}

		void Bottle::Draw(Surface* gameScreen, vec2 bottlePosition)
		{
			//score++;
			//std::cout << score << std::endl;

			//bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);


			if (bottleSprite) {
				bottleSprite->Draw(gameScreen, static_cast<int>(bottlePosition.x), static_cast<int>(bottlePosition.y));
			}
		}

		void Bottle::ReDraw(Surface* screen)
		{
			//score++;
			//std::cout << "score" << std::endl;
			//std::cout << score << std::endl;

			bottlePosition = setDrawPosition();

			Draw(screen, bottlePosition);
		}

		void Bottle::HandleHit(vec2& ballPosition, Surface* screen, Bottle* myBottle)
		{

			float playerBallPositionX = ballPosition.x;
			float playerBallPositionY = ballPosition.y;

			vec2 validDrawPositions[5] = {
				vec2(200.0f, 100.0f),
				vec2(200.0f, 175.0f),
				vec2(200.0f, 250.0f),
				vec2(200.0f, 325.0f),
				vec2(200.0f, 400.0f)
			};

			int aX = static_cast<int>(playerBallPositionX);
			int aY = static_cast<int>(playerBallPositionY);
			int aWidth = 50;
			int aHeight = 50;

			int bX = 0;
			int bY = 0;
			int bWidth = 50;
			int bHeight = 50;



			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[0].x), static_cast<int>(validDrawPositions[0].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[0].x
				&& bottlePosition.y == validDrawPositions[0].y)
			{
				ReDraw(screen);
			}

			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[1].x), static_cast<int>(validDrawPositions[1].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[1].x
				&& bottlePosition.y == validDrawPositions[1].y)
			{
				ReDraw(screen);
			}

			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[2].x), static_cast<int>(validDrawPositions[2].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[2].x
				&& bottlePosition.y == validDrawPositions[2].y)
			{
				ReDraw(screen);
			}

			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[3].x), static_cast<int>(validDrawPositions[3].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[3].x
				&& bottlePosition.y == validDrawPositions[3].y)
			{
				ReDraw(screen);
			}

			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[4].x), static_cast<int>(validDrawPositions[4].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[4].x
				&& bottlePosition.y == validDrawPositions[4].y)
			{
				ReDraw(screen);
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
		ballPosition.y = ScreenHeight - static_cast<float>(ballSprite->GetHeight());
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
			  std::cout << gravity << std::endl;
			  if (gravity == 0.0f)
			  {
				  std::cout << "reach" << std::endl;
				  if (GetAsyncKeyState(VK_SPACE)) ballPosition.y -= 40.0f;
			  }

			  //if (GetAsyncKeyState(VK_SPACE)) ballPosition.y -= 10.0f;
			  if (GetAsyncKeyState(VK_LEFT)) ballPosition.x -= ballSpeed * deltaTime;
			  if (GetAsyncKeyState(VK_RIGHT)) ballPosition.x += ballSpeed * deltaTime;
			  if (GetAsyncKeyState(VK_DOWN)) ballPosition.y += ballSpeed * deltaTime;
			  if (GetAsyncKeyState(VK_UP)) ballPosition.y -= ballSpeed * deltaTime;

			  ballPosition.y += ballVelocity.y * gravity * deltaTime;
			  ballPosition.x += ballVelocity.x * gravity * deltaTime;

			  if (ballPosition.y + ballSprite->GetHeight() < screen->GetHeight()) {
				  ballPosition.y += gravity * deltaTime;
				  gravity += 1.5f;
			  }
		  }


		  void Player::CheckCollision()
		  {
			  int tileMinX = static_cast<int>(ballPosition.x / tileWidth);
			  int tileMinY = static_cast<int>(ballPosition.y / tileHeight);
			  int tileMaxX = static_cast<int>((ballPosition.x + 50) / tileWidth);
			  int tileMaxY = static_cast<int>((ballPosition.y + 50) / tileHeight);
			  int tileNew = static_cast<int>((ballPosition.y + 49) / tileHeight);

			  if (ballPosition.y + ballSprite->GetHeight() > screen->GetHeight())
			  {
				  ballPosition.y = screen->GetHeight() - static_cast<float>(ballSprite->GetHeight());
				  gravity = 0.0f;
			  }

			  // Check for collisions and reset position if necessary
			  if (map[tileMinY][tileMinX * 3 + 2] == 'X'
				  && map[tileMaxY][tileMinX * 3 + 2] != 'X') {
				  ballPosition.x = prevBallPosition.x;
				  ballPosition.y = prevBallPosition.y;
			  }
			  if (map[tileMinY][tileMaxX * 3 + 2] == 'X'
				  && map[tileMaxY][tileMaxX * 3 + 2] != 'X') {
				  ballPosition.x = prevBallPosition.x;
				  ballPosition.y = prevBallPosition.y;
			  }


			  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X'
				  && map[tileNew][tileMaxX * 3 + 2] != 'X') {
				  ballPosition.x = prevBallPosition.x;
				  ballPosition.y = prevBallPosition.y - 0.1f;
				  gravity = 0.0f;
			  }
			  if (map[tileMaxY][tileMinX * 3 + 2] == 'X'
				  && map[tileNew][tileMinX * 3 + 2] != 'X') {
				  ballPosition.x = prevBallPosition.x;
				  ballPosition.y = prevBallPosition.y - 0.1f;
				  gravity = 0.0f;

			  }
			  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X'
				  && map[tileNew][tileMaxX * 3 + 2] == 'X') {
				  ballPosition.x = prevBallPosition.x;
				  ballPosition.y = prevBallPosition.y;
				  //gravity = 0.0f;
			  }
			  if (map[tileMaxY][tileMinX * 3 + 2] == 'X'
				  && map[tileNew][tileMinX * 3 + 2] == 'X') {
				  ballPosition.x = prevBallPosition.x;
				  ballPosition.y = prevBallPosition.y;
				  //gravity = 0.0f;
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
		//myBottle->Spawn(screen, myBottle->bottlePosition);

	}

	void Game::Init() {}


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
		myBottle->HandleHit(myPlayer->ballPosition, myPlayer->screen, myBottle);

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
		//screen->Box(myBottle->bottlePosition.x, myBottle->bottlePosition.y, myBottle->bottlePosition.x + myBottle->bottleSprite->GetWidth(), myBottle->bottlePosition.y + myBottle->bottleSprite->GetHeight(), 0xffff00);
		myPlayer->ballSprite->Draw(screen, static_cast<int> (myPlayer->ballPosition.x), static_cast<int>(myPlayer->ballPosition.y));
		//screen->Box(myPlayer->ballPosition.x, myPlayer->ballPosition.y, myPlayer->ballPosition.x + myPlayer->ballSprite->GetWidth(), myPlayer->ballPosition.y + static_cast<float> (myPlayer->ballSprite->GetHeight()), 0xffff00);
	}
};