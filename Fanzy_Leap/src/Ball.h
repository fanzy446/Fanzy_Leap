#ifndef BALL_HPP
#define BALL_HPP
#include "SurfaceClass.h"
#include <string>
#include "ExternValue.h"

class Ball
{
public:
	Ball(int x, int y, int speedX, int g, const std::string& _hero, const ScreenSurface& _screen);
	int getX();
	int getY();
	void move();
	void show();
	void goon();
	void stop();
public:
	bool pause;
	int X;
	int Y;
	int G;
	int speedX;
	int speedY;
	PictureSurface hero;
};
#endif