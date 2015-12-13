#include "Thing.h"


Thing::Thing(int _kind, int _beginX, int _beginY, int _speedX, int _speedY, const std::string& mattername, const ScreenSurface& _screen):
kind(_kind), beginX(_beginX), beginY(_beginY), X(_beginX), Y(_beginY), speedX(_speedX), speedY(_speedY), act(false), pause(false), matter(mattername, _screen)
{
	matter.colorKey(65, 98, 103);
}

void Thing::move()
{
	if(act == true && pause == false)
	{
		if(kind == 1)
		{
			X += speedX;
			if((speedX > 0 && X > SCREEN_W)||(speedX < 0 && X < -THING_H))
			{
				reset();
			}
		}
		else if(kind == 2)
		{
			X += speedX;
			speedY += 1;
			Y += speedY;
			if(Y > SCREEN_H - THING_H)
			{
				Y = SCREEN_H - THING_H;
				speedY = -speedY;
			}
			if((speedX > 0 && X > SCREEN_W)||(speedX < 0 && X < -THING_W))
			{
				speedY = 0;
				reset();
			}
		}
		else if (kind == 3)
		{
			Y += speedY;
			if(Y > SCREEN_H)
			{
				reset();
			}
		}
	}
}

void Thing::show()
{
	if(act == true && pause == false)
	{	
		matter.blit(X, Y);
	}
}

void Thing::activate()
{
	act = true;
}

void Thing::stop()
{
	pause = true;
}

void Thing::goon()
{
	pause = false;
}

void Thing::reset()
{
	X = beginX;
	Y = beginY;
	act = false;
}

int Thing::getX()
{
	return X;
}

int Thing::getY()
{
	return Y;
}

void Thing::set(int x, int y)
{
	X = x;
	Y = y;
}

bool Thing::getS()
{
	if(act == false)
		return false;
	else
		return true;
}