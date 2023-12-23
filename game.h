#pragma once
#include "template.h"

namespace Tmpl8 {

class Surface;
class Sprite;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
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
	Sprite* ballSprite;
	vec2 ballPosition;
	vec2 prevBallPosition{ballPosition.x, ballPosition.y};
	vec2 ballSize;
	vec2 ballVelocity{ 0, 0 };
	float gravity = 0.0f;
	float ballSpeed = 100.0f;
	bool isAllowed = true;
	const int tileWidth = 32;
	const int tileHeight = 32;
	

};

}; // namespace Tmpl8