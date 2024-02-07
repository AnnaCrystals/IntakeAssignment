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

			 int tileMaxYNew = tileMaxY -1;

			 //Both bottom sides
			 if (collisionMap->map[0][tileMaxY][tileMinX] == 88
				 && collisionMap->map[0][tileMaxY][tileMaxX] == 88)
			 {
				 playerPosition.y = prevPlayerPosition.y;
				 playerVelocity.y = 0.0f;
			 } 

			 //Either one of the bottom sides
			 else if (collisionMap->map[0][tileMaxY][tileMinX] == 88 
				 || collisionMap->map[0][tileMaxY][tileMaxX] == 88)
			 {
				 playerPosition.y = prevPlayerPosition.y;
				 playerVelocity.y = 0.0f;
			 }



			 //Both top sides
			 if (collisionMap->map[0][tileMinY][tileMinX] == 88
				 && collisionMap->map[0][tileMinY][tileMaxX] == 88)
			 {
				 playerPosition.y = prevPlayerPosition.y;
				 playerVelocity.y = 0.0f;
			 } 

			 //Either one of the top sides
			 else if (collisionMap->map[0][tileMinY][tileMinX] == 88
				 || collisionMap->map[0][tileMinY][tileMaxX] == 88)
			 {
				 playerPosition.y = prevPlayerPosition.y;
				 playerVelocity.y = 0.0f;
			 }


			 //Left side
			 if (collisionMap->map[0][tileMaxY][tileMinX] == 88
				 && collisionMap->map[0][tileNew][tileMinX] == 88
				 || collisionMap->map[0][tileMinY][tileMinX] == 88
				 && collisionMap->map[0][tileNew][tileMinX] == 88)
			 {
				 playerPosition.x = prevPlayerPosition.x;

				 
			 }
			 else if (collisionMap->map[0][tileMaxY][tileMinX] == 88)
			 {
				 std::cout << "hit left" << std::endl;
			 }
			 
			 

			 //Right side
			 if (collisionMap->map[0][tileMaxY][tileMaxX] == 88
				 && collisionMap->map[0][tileNew][tileMaxX] == 88
				 || collisionMap->map[0][tileMinY][tileMaxX] == 88
				 && collisionMap->map[0][tileNew][tileMaxX] == 88)
			 {
				 playerPosition.x = prevPlayerPosition.x;
				 
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