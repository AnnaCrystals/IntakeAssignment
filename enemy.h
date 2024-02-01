#pragma once
#pragma once
#include "template.h"
#include "surface.h"
#include "bottle.h"
#include "game.h"


namespace Tmpl8
{

	class Enemy 
	{
	public:
		Enemy()
		{
			enemySprite = new Sprite(new Surface("assets/Bridget_Guilty_Gear.png"), 1);
		}

		Surface* screen;
		Sprite* enemySprite;

		float enemyHeight;
		float enemyWidth;

	private:


	};
};