#ifndef MAIN
#define MAIN
#include "SurfaceClass.h"
#include "game_loop.h"
#include <vector>
int main(int argc ,char* argv[])
{
	int mainRtn = 0;
	SDL_Thread* thread = 0;
	try 
	{
		mainRtn = game(0);
	}
	catch ( const ErrorInfo& info ) 
	{
		info.show();
		return -1;
	}
	return mainRtn;
}
#endif