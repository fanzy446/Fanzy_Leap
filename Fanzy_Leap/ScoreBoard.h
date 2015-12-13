#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H
#include "SurfaceClass.h"
#include "int_to_string.h"
#include "StringData.h"
#include "string"

class ScoreBoard
{
private:
	TextSurface Score;
	int score;
	int X;
	int Y;
public:
	ScoreBoard(int at_x, int at_y, const ScreenSurface& _screen);
	void setup(int at_x, int at_y);
	void setmessage(const std::string message);
	void setsize(int size);
	void setcolor(Uint8 _r, Uint8 _g, Uint8 _b);
	void setfont(const std::string& ttf_fileName);
	void blit_play();
	void blit_end();
	void addpoint(int num);
	SDL_Surface* point();
	int getScore();
};
#endif