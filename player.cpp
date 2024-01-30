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
};