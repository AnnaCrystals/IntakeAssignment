#pragma once
#include "template.h"
#include "surface.h"
#include "bottle.h"
#include "game.h"


namespace Tmpl8 {

	class Surface;
	class Sprite;
	class Bottle;

	class Map 
	{
	public:
		Map();

		void Map::LoadMap(const char* loadFile, const int layer);

		int map[1][16][25] = {};
		int loadedLayers = 0;

	private:

};

};