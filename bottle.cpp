#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL_scancode.h>
#include "bottle.h"
#include "player.h"

namespace Tmpl8
{
		void Bottle::SetPlayer(Player* myPlayer) {
			this->myPlayer = myPlayer;
		}

		bool Bottle::AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
		{
			//Check if object A collides with object B by checking if both axes cross with each other 
			return aX < bX + bWidth &&
				aX + aWidth >= bX &&
				aY <= bY + bHeight &&
				aY + aHeight >= bY;
		}

		int Bottle::RandomNumber()
		{
			static int previousNumber = 0;

			//Seeding the RandomNumber function so it gets more 'random' by using time
			srand(static_cast<unsigned int>(time(0)));

			int newNumber;

			//While loop gets executed once since newNumber won't be equal to 0 
			//Every time the newNumber IS equal to the previousNumber it repeats until it's not equal
			//Doing this there are no repititions being used
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
			int number = RandomNumber();

			//Returns are drawPositions for the bottlesprite based on the random number
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
			//If bottleSprite is true draw the bottleSprite
			if (bottleSprite) 
			{
				bottleSprite->Draw(gameScreen, static_cast<int>(bottlePosition.x), static_cast<int>(bottlePosition.y));
			}
		}

		void Bottle::ReDraw(Surface* screen)
		{		 
			//Returns the new drawPositions for the bottleSprite
			bottlePosition = SetDrawPosition();

			Draw(screen, bottlePosition);
		}

		void Bottle::HandleHit(vec2& playerPosition, Surface* screen, Bottle* myBottle)
		{

			//A IS PLAYER COORDINATES UPDATE THIS STUFF
			float playerPositionX = playerPosition.x;
			float playerPositionY = playerPosition.y;

			int aX = static_cast<int>(playerPositionX);
			int aY = static_cast<int>(playerPositionY);


			int aWidth = myPlayer->playerSprite->GetWidth();
			int aHeight = myPlayer->playerSprite->GetHeight();


			//B IS BOTTLE COORDINATES
			int bX = 0;
			int bY = 0;
			int bWidth = bottleSprite->GetWidth();
			int bHeight = bottleSprite->GetHeight();


			//If hit at 0 do a ReDraw
			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[0].x), static_cast<int>(validDrawPositions[0].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[0].x
				&& bottlePosition.y == validDrawPositions[0].y)
			{
				ReDraw(screen);
			}

			//If hit at 1 do a ReDraw
			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[1].x), static_cast<int>(validDrawPositions[1].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[1].x
				&& bottlePosition.y == validDrawPositions[1].y)
			{
				ReDraw(screen);
			}

			//If hit at 2 do a ReDraw
			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[2].x), static_cast<int>(validDrawPositions[2].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[2].x
				&& bottlePosition.y == validDrawPositions[2].y)
			{
				ReDraw(screen);
			}

			//If hit at 3 do a ReDraw
			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[3].x), static_cast<int>(validDrawPositions[3].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[3].x
				&& bottlePosition.y == validDrawPositions[3].y)
			{
				ReDraw(screen);
			}

			//If hit at 4 do a ReDraw
			if (AABB(aX, aY, aWidth, aHeight,
				static_cast<int>(validDrawPositions[4].x), static_cast<int>(validDrawPositions[4].y), bWidth, bHeight)
				&& bottlePosition.x == validDrawPositions[4].x
				&& bottlePosition.y == validDrawPositions[4].y)
			{
				ReDraw(screen);
			}

		}
	
};