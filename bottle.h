#pragma once
#include "template.h"


namespace Tmpl8 {

	class Surface;
	class Sprite;
	class Player;
	class Bottle;

	class Bottle
	{
	public:
		Bottle()
		{
			bottlePosition.x = 200.0f;
			bottlePosition.y = 100.0f;
			bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);
			score = 0;
			bottleHeight = 50.0f;
			bottleWidth = 50.0f;

		}

		Sprite* bottleSprite;

		vec2 bottlePosition;

		vec2 validDrawPositions[5] =
		{
			vec2(200.0f, 100.0f),
			vec2(200.0f, 175.0f),
			vec2(200.0f, 250.0f),
			vec2(200.0f, 325.0f),
			vec2(200.0f, 400.0f)
		};

		float bottleHeight;
		float bottleWidth;
		int score;


		bool Bottle::AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight);
		int Bottle::RandomNumber();
		vec2 Bottle::SetDrawPosition();
		void Bottle::Draw(Surface* gameScreen, vec2 bottlePosition);
		void Bottle::ReDraw(Surface* screen);
		void Bottle::HandleHit(vec2& ballPosition, Surface* screen, Bottle* myBottle);
		void Bottle::SetPlayer(Player* player);

	private:
		Surface* screen;
		Player* myPlayer;
		Bottle* myBottle;
		Bottle* newBottle;
	};


};
