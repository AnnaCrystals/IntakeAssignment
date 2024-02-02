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

			  //if (GetAsyncKeyState(VK_DOWN)) playerPosition.y += playerSpeed * deltaTime;
			  //if (GetAsyncKeyState(VK_UP)) playerPosition.y -= playerSpeed * deltaTime;

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

			  int tileNew = static_cast<int>((playerPosition.y + playerSprite->GetHeight() - 2.0f )  / tileHeight);

			  //Check if object player has hit bottom screen
			  if (playerPosition.y + playerSprite->GetHeight() > screen->GetHeight())
			  {
				  playerPosition.y = screen->GetHeight() - static_cast<float>(playerSprite->GetHeight());
				  playerVelocity.y = 0.0f;
			  }

			  // Check if object player TOP SIDE LEFT has hit an 'X'
			  if (map[tileMinY][tileMinX * 3 + 2] == 'X'
				  && map[tileMaxY][tileMinX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
				  playerVelocity.y = 0.0f;
			  }

			  // Check if object player TOP SIDE RIGHT has hit an 'X'
			  else if (map[tileMinY][tileMaxX * 3 + 2] == 'X'
				  && map[tileMaxY][tileMaxX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
				  playerVelocity.y = 0.0f;
			  }

			  //Check if object player BOTTOM SIDE LEFT has hit an 'X'
			  if (map[tileMaxY][tileMinX * 3 + 2] == 'X'
				  && map[tileNew][tileMinX * 3 + 2] != 'X')
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y - 0.1f;
				  playerVelocity.y = 0.0f;

			  }
			  //Check if object player BOTTOM SIDE RIGHT has hit an 'X'
			  else if (map[tileMaxY][tileMaxX * 3 + 2] == 'X'
				  && map[tileNew][tileMaxX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y -0.1f;
				  playerVelocity.y = 0.0f;
			  }

			  
			  //Check if object player RIGHT SIDE BOTTOM has hit an 'X'
			  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X'
				  && map[tileNew][tileMaxX * 3 + 2] == 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
				  playerVelocity.y = 0.0f;
			  }

			  //Check if object player LEFT SIDE BOTTOM has hit an 'X'
			  else if (map[tileMaxY][tileMinX * 3 + 2] == 'X'
				  && map[tileNew][tileMinX * 3 + 2] == 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
				  playerVelocity.y = 0.0f;
			  }
		  }

		  void Player::HandleCollision(float deltaTime)
		  {
			  prevPlayerPosition.y = playerPosition.y;
			  prevPlayerPosition.x = playerPosition.x;
			  prevGravity = gravity;

			  UpdatePosition(deltaTime);
			  CheckCollision();
		  }	

};