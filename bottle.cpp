#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL_scancode.h>
#include "bottle.h"

namespace Tmpl8
{

		bool Bottle::AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
		{
			return aX < bX + bWidth &&
				aX + aWidth >= bX &&
				aY <= bY + bHeight &&
				aY + aHeight >= bY;
		}

		int Bottle::RandomNumber()
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

		vec2 Bottle::SetDrawPosition()
		{
			vec2 validDrawPositions[5] = {
				vec2(200.0f, 100.0f),
				vec2(200.0f, 175.0f),
				vec2(200.0f, 250.0f),
				vec2(200.0f, 325.0f),
				vec2(200.0f, 400.0f)
			};

			int number = RandomNumber();

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

			bottlePosition = SetDrawPosition();

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