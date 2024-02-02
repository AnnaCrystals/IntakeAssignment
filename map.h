#pragma once
#include "template.h"
#include "surface.h"
#include "bottle.h"
#include "game.h"
#include <string>
#include <vector>



namespace Tmpl8 {

	class Surface;
	class Sprite;
	class Bottle;
	class Screen;

	class Map
	{
	public:
		Map();

		void Map::LoadMap(const char* nameFile, const int layer);


		int map[1][16][25] = {};
		int loadedLayers = 0;


		struct MapLayer {
			vec2 map[16][25];
		};

		struct MapData {
			std::vector<MapLayer> layers;
			MapLayer collisionLayer;
		};

		static void FolderRead();

		Sprite tileMap = Sprite(new Surface("assets/.....tilemap hier toevoegen"), 1);

	private:
		std::string TextFileRead(const char* nameFile);

	};

};