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
			  /*if (gravity == 0.0f)
			  {
				  if (GetAsyncKeyState(VK_SPACE)) playerPosition.y -= 40.0f;
			  }*/

			  if (GetAsyncKeyState(VK_SPACE)) playerPosition.y -= 10.0f;
			  if (GetAsyncKeyState(VK_LEFT)) playerPosition.x -= playerSpeed * deltaTime;
			  if (GetAsyncKeyState(VK_RIGHT)) playerPosition.x += playerSpeed * deltaTime;
			  if (GetAsyncKeyState(VK_DOWN)) playerPosition.y += playerSpeed * deltaTime;
			  if (GetAsyncKeyState(VK_UP)) playerPosition.y -= playerSpeed * deltaTime;

			  playerPosition.y += playerVelocity.y * gravity * deltaTime;
			  playerPosition.x += playerVelocity.x * gravity * deltaTime;

			  if (playerPosition.y + playerSprite->GetHeight() < screen->GetHeight()) 
			  {
				  playerPosition.y += gravity * deltaTime;
				  gravity += 1.5f;
			  }
		  }


		  void Player::CheckCollision()
		  {
			  int tileMinX = static_cast<int>(playerPosition.x / tileWidth);
			  int tileMinY = static_cast<int>(playerPosition.y / tileHeight);
			  int tileMaxX = static_cast<int>((playerPosition.x + 50) / tileWidth);
			  int tileMaxY = static_cast<int>((playerPosition.y + 50) / tileHeight);
			  int tileNew = static_cast<int>((playerPosition.y + 49) / tileHeight);

			  if (playerPosition.y + playerSprite->GetHeight() > screen->GetHeight())
			  {
				  playerPosition.y = screen->GetHeight() - static_cast<float>(playerSprite->GetHeight());
				  gravity = 0.0f;
			  }

			  // Check for collisions and reset position if necessary
			  if (map[tileMinY][tileMinX * 3 + 2] == 'X'
				  && map[tileMaxY][tileMinX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
			  }

			  if (map[tileMinY][tileMaxX * 3 + 2] == 'X'
				  && map[tileMaxY][tileMaxX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
			  }


			  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X'
				  && map[tileNew][tileMaxX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y - 0.1f;
				  gravity = 0.0f;
			  }

			  if (map[tileMaxY][tileMinX * 3 + 2] == 'X'
				  && map[tileNew][tileMinX * 3 + 2] != 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y - 0.1f;
				  gravity = 0.0f;

			  }

			  if (map[tileMaxY][tileMaxX * 3 + 2] == 'X'
				  && map[tileNew][tileMaxX * 3 + 2] == 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
				  //gravity = 0.0f;
			  }

			  if (map[tileMaxY][tileMinX * 3 + 2] == 'X'
				  && map[tileNew][tileMinX * 3 + 2] == 'X') 
			  {
				  playerPosition.x = prevPlayerPosition.x;
				  playerPosition.y = prevPlayerPosition.y;
				  //gravity = 0.0f;
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