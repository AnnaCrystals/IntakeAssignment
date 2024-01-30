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
			/*bottlePosition.x = ScreenWidth / 2.0f + 100.0f;
			bottlePosition.y = ScreenHeight - 50.0f;*/

			bottlePosition.x = 200.0f;
			bottlePosition.y = 100.0f;
			bottleSprite = new Sprite(new Surface("assets/Pot21.png"), 1);

		}



		bool Bottle::AABB(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight);
		int Bottle::RandomNumber();
		vec2 Bottle::SetDrawPosition();
		void Bottle::Draw(Surface* gameScreen, vec2 bottlePosition);
		void Bottle::ReDraw(Surface* screen);
		void Bottle::HandleHit(vec2& ballPosition, Surface* screen, Bottle* myBottle);

	
		Sprite* bottleSprite;
		vec2 bottlePosition;
		//Bottle* newBottle;



		const float bottleHeight = 50.0f;
		const float bottleWidth = 50.0f;
		bool despawned = false;
		int score = 0;

	private:
		Surface* screen;
		Player* myPlayer;
		Bottle* myBottle;
		Bottle* newBottle;
	};


}
