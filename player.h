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
		Player(char(*gameMap)[76], Surface* screen) : screen(screen), map(gameMap)
		{
			ballSprite = new Sprite(new Surface("assets/ball.png"), 1);
			ballSize.x = ballSprite->GetWidth() / 2.0f;
			ballSize.y = ballSprite->GetHeight() / 2.0f;
			ballPosition.x = ScreenWidth / 2.0f;
			ballPosition.y = ScreenHeight - static_cast<float>(ballSprite->GetHeight());
		}

		void Player::UpdatePosition(float deltaTime);
		void Player::CheckCollision();
		void Player::HandleCollision(float deltaTime);




		Sprite* ballSprite;
		//Surface* screen;

		vec2 ballPosition;
		vec2 prevBallPosition{ ballPosition.x, ballPosition.y };
		vec2 ballSize;
		vec2 ballVelocity{ 0, 0 };

		float gravity = 0.0f;
		float prevGravity;

		const int tileWidth = 32;
		const int tileHeight = 32;
		float ballSpeed = 120.0f;


		Surface* screen;

	private:
		
		Player* myPlayer;
		Bottle* myBottle;
		Bottle* newBottle;
		char(*map)[76];
	};



}; // namespace Tmpl8
