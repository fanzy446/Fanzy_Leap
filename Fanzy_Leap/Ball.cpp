#include "Ball.h"


Ball::Ball(int x, int y, int _speedX, int g, const std::string& _hero, const ScreenSurface& _screen):
X(x), Y(y), G(g), speedX(_speedX), speedY(0), pause(false), hero(_hero, _screen)
{
	hero.colorKey(67, 102, 106);
}

void Ball::move()
{
	if(pause == false)
	{
		Uint8* keys;
		keys = SDL_GetKeyState(0);
		if ( keys[SDLK_LEFT]|| keys[SDLK_a] )
		{
			X -= speedX;
		}
		else if ( keys[SDLK_RIGHT]|| keys[SDLK_d] )
		{
			X += speedX;
		}
		speedY += G;
		Y += speedY;
		if(X < 0)	
			X = 0;
		if(X > SCREEN_W - BALL_W)
			X = SCREEN_W - BALL_W;
		if(Y > SCREEN_H - BALL_H)
		{
			Y = SCREEN_H - BALL_H;
			speedY = -speedY;
		}
	}
}

int Ball::getX()
{
	return X;
}

int Ball::getY()
{
	return Y;
}

void Ball::show()
{
	if(pause == false)
	{
		hero.blit(X, Y);
	}
}

void Ball::goon()
{
	pause = false;
}

void Ball::stop()
{
	pause = true;
}