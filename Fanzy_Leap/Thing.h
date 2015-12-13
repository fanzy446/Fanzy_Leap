#ifndef THING_HPP
#define THING_HPP
#include "SurfaceClass.h"
#include <string>
#include "ExternValue.h"

class Thing
{
public:
	Thing(int _kind, int _beginX, int _beginY, int _speedX, int _speedY,const std::string& mattername, const ScreenSurface& _screen);
	void move();
	void show();
	void activate();
	void reset();
	void stop();
	void goon();
	int getX();
	int getY();
	bool getS();
	void set(int x, int y);
private:
	bool pause;
	bool act;
	int kind;
	int beginX;
	int beginY;
	int X;
	int Y;
	int speedX;
	int speedY;
	PictureSurface matter;
};
#endif