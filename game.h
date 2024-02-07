#pragma once
#include "template.h"
#include "map.h" // Include Map.h where needed, but not here
#include "surface.h"
#include "bottle.h"
#include <string>
#include <vector>


namespace Tmpl8 {

	class Surface;
	class Sprite;
	class Player;
	class Bottle;
	class Map;

	class Game
	{
	public:
		Game();

		void SetTarget(Surface* surface);
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { /* implement if you want to detect mouse movement */ }
		void KeyUp(int key) {}
		void KeyDown(int key) {}

	private:
		Surface* screen;
		Player* myPlayer;
		Bottle* myBottle;
		Bottle* newBottle;
		Map myMap;
		Map collisionMap;
	};



}; // namespace Tmpl8