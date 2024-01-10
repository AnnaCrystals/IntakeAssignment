#pragma once
#include "template.h"


namespace Tmpl8 {

class Surface;
class Sprite;
class Player;
class Bottle;

class Game
{
public:
	Game();

	void SetTarget(Surface* surface);
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key) {}
	void KeyDown(int key) {}

private:
	Surface* screen;
	Player* myPlayer;
	Bottle* myBottle;
	Bottle* newBottle;
};



}; // namespace Tmpl8