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


		 void Player::CheckCollision() {
			 const Player::Rect player = { playerPosition.x, playerSprite->GetWidth(), playerPosition.y, playerSprite->GetHeight() };

			 // Calculate player bounding boxes for each side
			 Player::Rect playerBottom = { playerPosition.x, playerSprite->GetWidth(), playerPosition.y + playerSprite->GetHeight(), 1.f };
			 Player::Rect playerLeft = { playerPosition.x, 1.f, playerPosition.y, playerSprite->GetHeight() };
			 Player::Rect playerRight = { playerPosition.x + playerSprite->GetWidth() - 1.f, 1.f, playerPosition.y, playerSprite->GetHeight() };
			 Player::Rect playerTop = { playerPosition.x, playerSprite->GetWidth(), playerPosition.y - 1.f, 1.f };

			 // Calculate nearby tiles and the middle tile
			 int tileMiddleX = static_cast<int>((playerPosition.x + playerSprite->GetWidth() / 2) / tileWidth);
			 int tileMiddleY = static_cast<int>((playerPosition.y + playerSprite->GetHeight() / 2) / tileHeight);

			 std::vector<Location> locationsToCheck;

			 for (int x = -1; x < 2; x++) {
				 for (int y = -1; y < 2; y++) {
					 if (collisionMap->map[0][(tileMiddleY + y)][(tileMiddleX + x)] == solidTile) {
						 locationsToCheck.push_back(Location{ Rect{ static_cast<float>((tileMiddleX + x) * tileWidth), static_cast<float>(tileWidth), static_cast<float>((tileMiddleY + y) * tileHeight), static_cast<float>(tileHeight) }, (tileMiddleX + x), (tileMiddleY + y) });
					 }
				 }
			 }

			 for (Location location : locationsToCheck) {
				 if (intersects(playerBottom, location.rectangle)) {
					 playerPosition.y = location.rectangle.top - player.height;
					 playerVelocity.y = 0.0f;
				 }
				 if (intersects(playerLeft, location.rectangle)) {
					 // Adjust player position to resolve collision
					 playerPosition.x = location.rectangle.left + location.rectangle.width + 1.f;
				 }
				 if (intersects(playerRight, location.rectangle)) {
					 playerPosition.x = location.rectangle.left - player.width - 1.f;
				 }
				 if (intersects(playerTop, location.rectangle)) {
					 playerPosition.y = location.rectangle.top + location.rectangle.height + 1.f;
					 playerVelocity.y = 0.0f;
				 }
			 }
		 }


		  void Player::HandleCollision(float deltaTime)
		  {
			  prevPlayerPosition.y = playerPosition.y;
			  prevPlayerPosition.x = playerPosition.x;

			  UpdatePosition(deltaTime);
			  CheckCollision();
		  }	


		  bool Player::intersects(Rect& rectangle1, Rect& rectangle2)
		  {
			  float r1MinX = (_STD min)(rectangle1.left, static_cast<float>(rectangle1.left + rectangle1.width));
			  float r1MaxX = (_STD max)(rectangle1.left, static_cast<float>(rectangle1.left + rectangle1.width));
			  float r1MinY = (_STD min)(rectangle1.top, static_cast<float>(rectangle1.top + rectangle1.height));
			  float r1MaxY = (_STD max)(rectangle1.top, static_cast<float>(rectangle1.top + rectangle1.height));

			  float r2MinX = (_STD min)(rectangle2.left, static_cast<float>(rectangle2.left + rectangle2.width));
			  float r2MaxX = (_STD max)(rectangle2.left, static_cast<float>(rectangle2.left + rectangle2.width));
			  float r2MinY = (_STD min)(rectangle2.top, static_cast<float>(rectangle2.top + rectangle2.height));
			  float r2MaxY = (_STD max)(rectangle2.top, static_cast<float>(rectangle2.top + rectangle2.height));

			  float interLeft = (_STD max)(r1MinX, r2MinX);
			  float interTop = (_STD max)(r1MinY, r2MinY);
			  float interRight = (_STD min)(r1MaxX, r2MaxX);
			  float interBottom = (_STD min)(r1MaxY, r2MaxY);

			  if ((interLeft < interRight) && (interTop < interBottom))
			  {
				  return true;
			  }
			  return false;
		  }
};