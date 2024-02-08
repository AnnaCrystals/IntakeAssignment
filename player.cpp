#include "player.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL_scancode.h>




namespace Tmpl8
{
		 void Player::UpdatePosition(float deltaTime)
		 {
			 static bool spacePressed = false;

			 //SPACE can only be pressed if gravity = 0.0f
			 if (playerVelocity.y == 0.0f)
			 {
				 if (GetAsyncKeyState(VK_SPACE))
				 {
					 //!spacePressed makes sure that the player isn't holding the key
					 if (!spacePressed)
					 {

						 playerVelocity.y -= 300.0f;
						 spacePressed = true;
					 }
				 }
				 else
				 {
					 spacePressed = false;
				 }
			 }


			 if (GetAsyncKeyState(VK_LEFT)) playerPosition.x -= playerSpeed * deltaTime;
			 if (GetAsyncKeyState(VK_RIGHT)) playerPosition.x += playerSpeed * deltaTime;

			 playerPosition.y += playerVelocity.y * deltaTime;
			 playerPosition.x += playerVelocity.x * deltaTime;

			 if (playerPosition.y + playerSprite->GetHeight() < screen->GetHeight())
			 {
				 playerVelocity.y += gravity * deltaTime;
				 playerVelocity.y += 9.81f;
			 }

		  }


         void Player::CheckCollision()
         {
             int tileMinX = static_cast<int>(playerPosition.x / tileWidth);
             int tileMinY = static_cast<int>(playerPosition.y / tileHeight);
             int tileMaxX = static_cast<int>((playerPosition.x + playerSprite->GetWidth()) / tileWidth);
             int tileMaxY = static_cast<int>((playerPosition.y + playerSprite->GetHeight()) / tileHeight);

             int tileNew = static_cast<int>((playerPosition.y + playerSprite->GetHeight() / 2.0f) / tileHeight);

             int tileMinXNew = static_cast<int>(playerPosition.x / tileWidth) + 1;
             int tileMaxXNew = static_cast<int>((playerPosition.x + playerSprite->GetWidth()) / tileWidth) + 1;

             int tileMaxYNew = static_cast<int>((playerPosition.y + playerSprite->GetHeight()) / tileHeight) - 1;
             int tileMinYNew = static_cast<int>(playerPosition.y / tileHeight) + 1;


             // Check collision on left side
             if ((collisionMap->map[0][tileMaxY][tileMinX] == solidTile
                 && collisionMap->map[0][tileNew][tileMinX] == solidTile)
                 ||(collisionMap->map[0][tileMinY][tileMinX] == solidTile
                 && collisionMap->map[0][tileNew][tileMinX] == solidTile))
             {
                 std::cout << "hit left" << std::endl;
                 playerPosition.x = prevPlayerPosition.x;
             }


             // Check collision on right side
             if ((collisionMap->map[0][tileMaxY][tileMaxX] == solidTile
                 && collisionMap->map[0][tileNew][tileMaxX] == solidTile)
                 ||(collisionMap->map[0][tileMinY][tileMaxX] == solidTile
                 && collisionMap->map[0][tileNew][tileMaxX] == solidTile))
             {
                 std::cout << "hit right" << std::endl;
                 playerPosition.x = prevPlayerPosition.x - 1.0f;
             }


             // Check collision on both bottom sides
             if (collisionMap->map[0][tileMaxY][tileMinX] == solidTile
                 && collisionMap->map[0][tileMaxY][tileMaxX] == solidTile)
             {
                 std::cout << "hit both bottom" << std::endl;
                 playerPosition.y = prevPlayerPosition.y;
                 playerVelocity.y = 0.0f;
             }


             // Check collision on either bottom side
             else if (collisionMap->map[0][tileMaxY][tileMinX] == solidTile
                 || collisionMap->map[0][tileMaxY][tileMaxX] == solidTile)
             {
                 if (collisionMap->map[0][tileMaxYNew][tileMinX] == solidTile)
                 {
                     playerPosition.x = prevPlayerPosition.x - 1.0f;
                     std::cout << "update" << std::endl;
                 }
                 if (collisionMap->map[0][tileMaxYNew][tileMinX] == solidTile)
                 {
                     playerPosition.x = prevPlayerPosition.x + 1.0f;
                     std::cout << "update" << std::endl;
                 }
                 std::cout << "hit either bottom" << std::endl;
                 playerPosition.y = prevPlayerPosition.y;
                 playerVelocity.y = 0.0f;
             }




             // Check collision on both top sides
             if (collisionMap->map[0][tileMinY][tileMinX] == solidTile
                 && collisionMap->map[0][tileMinY][tileMaxX] == solidTile)
             {
                 std::cout << "hit both top" << std::endl;
                 playerPosition.y = prevPlayerPosition.y;
                 playerVelocity.y = 0.0f;
             }




             // Check collision on either top side
             else if ((collisionMap->map[0][tileMinY][tileMinX] == solidTile
                 || collisionMap->map[0][tileMinY][tileMaxX] == solidTile)
                 && collisionMap->map[0][tileMinYNew][tileMinX] != solidTile
                 && collisionMap->map[0][tileMinYNew][tileMaxX] != solidTile)
             {
                 std::cout << "hit either top" << std::endl;
                 playerPosition.y = prevPlayerPosition.y;
                 playerVelocity.y = 0.0f;
             }
         }



		  void Player::HandleCollision(float deltaTime)
		  {
			  prevPlayerPosition.y = playerPosition.y;
			  prevPlayerPosition.x = playerPosition.x;

			  UpdatePosition(deltaTime);
			  CheckCollision();
		  }	

};