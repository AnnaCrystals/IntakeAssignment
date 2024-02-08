#pragma once
#include "template.h"
#include "surface.h"
#include "bottle.h"
#include "game.h"


namespace Tmpl8 {

	class Surface;
	class Sprite;
	class Bottle;

	class Player
	{
	public:
		Player(Map* collisionMap, Surface* screen) : screen(screen), collisionMap(collisionMap)
		{
			playerSprite = new Sprite(new Surface("assets/ball.png"), 1);

			playerSize.x = playerSprite->GetWidth() / 2.0f;
			playerSize.y = playerSprite->GetHeight() / 2.0f;

			//Initial player position
			playerPosition.x = ScreenWidth / 2.0f;
			playerPosition.y = ScreenHeight - static_cast<float>(playerSprite->GetHeight()) - 40.0f;
		}

		struct Rect
		{
			float left;
			float width;
			float top;
			float height;
		};
		struct Location
		{
			Rect rectangle;
			int x;
			int y;
		};


		static bool Player::intersects(Rect& rectangle1, Rect& rectangle2);

		

		Surface* screen;
		Sprite* playerSprite;

		vec2 playerPosition;
		vec2 prevPlayerPosition{ playerPosition.x, playerPosition.y };
		vec2 playerSize;
		vec2 playerVelocity{ 0, 0 };

		float gravity = 0.0f;
		float prevGravity;
		float playerSpeed = 150.0f;

		const int solidTile = 88;

		const int tileWidth = 32;
		const int tileHeight = 32;

		
		void Player::UpdatePosition(float deltaTime);
		void Player::CheckCollision();
		void Player::HandleCollision(float deltaTime);



	private:
		
		Player* myPlayer;
		Bottle* myBottle;
		Bottle* newBottle;
		Map* collisionMap;
		//char(*map)[76];
	};



}; // namespace Tmpl8
