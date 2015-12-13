#ifndef GAME_LOOP_H
#define GAME_LOOP_H


#include "StringData.h"
#include "ScoreBoard.h"
#include "SurfaceClass.h"
#include "ButtonClass.h"
#include "MixSoundClass.h"
#include "Thing.h"
#include "Ball.h"
#include "Timer.h"
#include <ctime>
#include <stdio.h>
#include "ExternValue.h"
#include "int_to_string.h"
#include <cmath>
#include <fstream>


int game(void* data);
bool LogoShow(const ScreenSurface& screen);
int StartMenu(const ScreenSurface& screen);
bool Help(const ScreenSurface& screen);
int GamePoccess(const ScreenSurface& screen);
bool Show3s(const ScreenSurface& screen);
int PauseMenu(const ScreenSurface& screen);
int GameEnd(const ScreenSurface& screen, ScoreBoard& score);
bool Hit(Ball& matter_h, Thing& matter_t);
#endif