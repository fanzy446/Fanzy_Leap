#include"ScoreBoard.h"


//*****************************************


//class ScoreBoard
ScoreBoard::ScoreBoard(int at_x, int at_y, const ScreenSurface& _screen):score(0), X(at_x), Y(at_y), Score("Score:0", _screen){}
void ScoreBoard::setup(int at_x, int at_y)
{
	X = at_x;
	Y = at_y;
}

void ScoreBoard::setmessage(const std::string message)
{
	Score.setMessage(message);
}

void ScoreBoard::setsize(int size)
{
	Score.setSize(size);
}

void ScoreBoard::setcolor(Uint8 _r, Uint8 _g, Uint8 _b)
{
	Score.setColor(_r, _g, _b);
}

void ScoreBoard::setfont(const std::string& ttf_fileName)
{
	Score.setFont(ttf_fileName);
}

void ScoreBoard::blit_play()
{
	StringData text("ScoreBoard");
	std::string temp=text[0] + int_to_string(score);
	Score.setMessage(temp);
	Score.blit(X, Y);
}

void ScoreBoard::blit_end()
{
	std::string temp=int_to_string(score);
	Score.setMessage(temp);
	Score.blit(X, Y);
}

void ScoreBoard::addpoint(int num)
{
	score += num;
}

SDL_Surface* ScoreBoard::point()
{
	return Score.point();
}

int ScoreBoard::getScore()
{
	return score;
}