#include"game_loop.h"

const std::string logo_img = "./images/Fanzy.png";

const std::string title_img = "./images/title.png";
const std::string startmenu_bg_img = "./images/startmenu_bg.png";
const std::string startmenu_b_out_img = "./images/begin_button_off.png";
const std::string startmenu_b_over_img = "./images/begin_button_over.png";
const std::string startmenu_b_mus = "./sounds/bg_mus.ogg";

const std::string help_bg_img = "./images/help_bg.png";
const std::string help_A_img = "./images/A.png";
const std::string help_D_img = "./images/D.png";
const std::string help_L_img = "./images/L.png";
const std::string help_R_img = "./images/R.png";
const std::string help_return_out_img = "./images/return_out.png";
const std::string help_return_over_img = "./images/return_over.png";

const std::string game_bg_img = "./images/game_bg.png";
const std::string game_bg_copy_img = "./images/game_bg_copy.png";
const std::string game_bg_slow_img = "./images/game_bg_slow.png";
const std::string game_bg_slow_copy_img = "./images/game_bg_slow_copy.png";
const std::string game_pause_out_img = "./images/pause_out.png";
const std::string game_pause_over_img = "./images/pause_over.png";
const std::string game_b_mus = "./sounds/game_mus.ogg";

const std::string hero_img = "./images/thing1.png";
const std::string thing_img = "./images/thing2.png";
const std::string crazy_img = "./images/thing3.png";
const std::string slow_img = "./images/thing4.png";
const std::string twice_img = "./images/thing5.png";

const std::string pausemenu_bg_img = "./images/dialog_bg.png";
const std::string pausemenu_b_out_img = "./images/begin_button_off.png";
const std::string pausemenu_b_over_img = "./images/begin_button_over.png";

const std::string gameend_bg_img = "./images/gameend_bg.png"; 
const std::string gameend_congratulations_img = "./images/congratulations.png"; 
const std::string gameend_b_out_img = "./images/begin_button_off.png";
const std::string gameend_b_over_img = "./images/begin_button_over.png";
const std::string gameend_b_mus = "./sounds/gameend.ogg";


const int FRAMES_PER_SECOND = 40;
const int GAME_TIME = 60;


EffectSound hit_mus("./sounds/hit.ogg");
EffectSound level1_mus("./sounds/level1.ogg");
EffectSound level2_mus("./sounds/level2.ogg");
EffectSound level3_mus("./sounds/level3.ogg");
EffectSound slow_start_mus("./sounds/slow_start.ogg");
EffectSound slow_end_mus("./sounds/slow_end.ogg");
EffectSound appear_mus("./sounds/game_appear.ogg");
EffectSound break_mus("./sounds/break_record.ogg");


int game(void* data)
{

	//Create a SDL screen.
	const Uint32 SCREEN_FLAGS = 0; //SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE
	const std::string WINDOW_NAME = "Leap v1.5   by Fanzy   2012/8/24";
	const std::string ICON_NAME = "logo.bmp";
	ScreenSurface screen(SCREEN_W, SCREEN_H, WINDOW_NAME, ICON_NAME, 0, SCREEN_FLAGS);
	int n = 1;
	//Fanzy Logo
	if(LogoShow(screen))
		n = 3;
	//main loop

	while(1)
	{
		switch(n)
		{
		case 1:n = StartMenu(screen);break;
		case 2:n = GamePoccess(screen);break;
		case 3:	return 0;
		default:		
			return -1;
		}
	}

}

int StartMenu(const ScreenSurface& screen)
{
	MusicSound mus(startmenu_b_mus);
	mus.play();
	StringData text("StartMenu");
	PictureSurface bg(startmenu_bg_img, screen);
	bg.blit();
	PictureSurface title(title_img, screen);
	title.colorKey(12, 39, 69);
	title.blit((SCREEN_W - title.point()->w) / 2, 20);
	int high;
	std::ifstream highscore;
	highscore.open( "HighScore.dat",std::ios::in|std::ios::binary);
	highscore.read((char *)&high, sizeof(int));
	if(high < 0 || high > 10000)
	{
		high = 0;
		std::ofstream newscore;
		newscore.open( "HighScore.dat",std::ios::out|std::ios::binary);
		newscore.write((char *)&high, sizeof(int));
		newscore.close();
	}
	highscore.close();
	TextSurface HighScore(text[3] + int_to_string(high), screen, 255, 255, 255, 30);
	HighScore.blit((SCREEN_W - HighScore.point() -> w) / 2, 195);
	Button B[3]=
	{
		Button(text[0], screen, 100, 0, 0, 255, 237, 11, 40),
		Button(text[1], screen, 100, 0, 0, 255, 237, 11, 40),
		Button(text[2], screen, 100, 0, 0, 255, 237, 11, 40)
	};

	B[0].setup((SCREEN_W - B[0].point() -> w) / 2, 250, 1);
	B[1].setup((SCREEN_W - B[1].point() -> w) / 2, 310, 1);
	B[2].setup((SCREEN_W - B[2].point() -> w) / 2, 370, 1);
	B[0].blitOut();
	B[1].blitOut();
	B[2].blitOut();
	screen.flip();
	SDL_Event game_event;
	while(1)
	{
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			bg.blit();
			HighScore.blit((SCREEN_W - HighScore.point() -> w) / 2, 195);
			title.blit((SCREEN_W - title.point()->w) / 2, 20);
			if(B[0].effectiveClick(game_event))
			{
				mus.stop();
				return 2;
			}
			else if(B[1].effectiveClick(game_event))
			{
				if(Help(screen))
					return 3;
				else
					break;
			}
			else if(B[2].effectiveClick(game_event))
			{
				mus.stop();
				return 3;
			}
			if(game_event.type == SDL_QUIT)
			{
				mus.stop();
				return 3;
			}
		}
		screen.flip();
		SDL_Delay(10);		
	}
}

int GamePoccess(const ScreenSurface& screen)
{
	StringData text("GamePoccess");
	int frame_ps = FRAMES_PER_SECOND;
	int left = GAME_TIME;
	bool crazy = false;
	int crazytime = left;
	bool slow = false;
	int slowtime = left;
	bool twice = false;
	int twicetime = left;
	int count = 0;
	int scount = 12;
	int hits = 0;
	int lasthitframe = 0;
	int frame = 0;
	int level = 0;
	SDL_Event game_event;
	//激活
	int tempf = 0;
	bool a = false;
	bool b = false;
	int n = 0;
	//加分
	int tempff = 0;
	bool c = false;
	int thits = 0;

	//音乐
	MusicSound mus(game_b_mus);
	mus.play();

	//3秒计时，音效
	if(Show3s(screen))
		return 3;

	//背景
	PictureSurface bg(game_bg_img,screen);
	PictureSurface bg_copy(game_bg_copy_img,screen);
	PictureSurface bg_slow(game_bg_slow_img,screen);
	PictureSurface bg_slow_copy(game_bg_slow_copy_img,screen);
	bg_copy.colorKey(65, 99, 103);
	bg_slow_copy.colorKey(97, 168, 213);
	//计分板显示
	ScoreBoard Score(25, 25, screen);
	Score.setsize(30);
	Score.blit_play();
	int high;
	std::ifstream highscore;
	highscore.open( "HighScore.dat",std::ios::in|std::ios::binary);
	highscore.read((char *)&high, sizeof(int));
	highscore.close();
	TextSurface HighScore(text[0]+ int_to_string(high), screen, 200, 0, 0, 20);
	TextSurface Hits(int_to_string(hits) + "Hits", screen, 0, 255, 174, 40, "./fonts/ARNPRIOR.TTF");	
	//暂停按钮
	Button Pause(game_pause_out_img,game_pause_over_img,screen);
	Pause.setup(650, 30 ,1);
	Pause.blitOut();

	screen.flip();

	Ball hero((SCREEN_W - BALL_W)/2, 60, 15, 1, hero_img, screen);
	Thing matter[28]=
	{
		Thing(1, - THING_W, 60, 8, 0, thing_img, screen),
		Thing(1, - THING_W, 120, 8, 0, thing_img, screen),
		Thing(1, - THING_W, 180, 8, 0, thing_img, screen),
		Thing(1, - THING_W, 240, 8, 0, thing_img, screen),
		Thing(1, - THING_W, 300, 8, 0, thing_img, screen),
		Thing(1, - THING_W, 360, 8, 0, thing_img, screen),
		Thing(1, - THING_W, 420, 8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 60, -8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 120, -8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 180, -8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 240, -8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 300, -8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 360, -8, 0, thing_img, screen),
		Thing(1, SCREEN_W, 420, -8, 0, thing_img, screen),
		Thing(2, - THING_W, 60, 8, 0, thing_img, screen),
		Thing(2, - THING_W, 120, 8, 0, thing_img, screen),
		Thing(2, - THING_W, 180, 8, 0, thing_img, screen),
		Thing(2, - THING_W, 240, 8, 0, thing_img, screen),
		Thing(2, - THING_W, 300, 8, 0, thing_img, screen),
		Thing(2, - THING_W, 360, 8, 0, thing_img, screen),
		Thing(2, - THING_W, 420, 8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 60, -8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 120, -8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 180, -8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 240, -8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 300, -8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 360, -8, 0, thing_img, screen),
		Thing(2, SCREEN_W, 420, -8, 0, thing_img, screen),
	};
	Thing Crazy(3, 0, -THING_H, 0, 8, crazy_img, screen);
	Thing Slow(3, 0, -THING_H, 0, 8, slow_img, screen);
	Thing Twice(3, 0, -THING_H, 0, 8, twice_img, screen);
	srand(time(0));


	while(1)
	{
		if(slow == false)
			bg.blit();
		else
			bg_slow.blit();
		//定义
		int temp = rand();
		TextSurface TimeLeft( int_to_string(left), screen, 0xFF, 0xFF, 0xFF, 80, "./fonts/argos.ttf");
		if(left <= 5)
			TimeLeft.setColor(200, 0, 0);
		Timer fps;
		fps.start();

		//球激活
		//普通球
		if(crazy == false)
		{
			if((frame % FRAMES_PER_SECOND == FRAMES_PER_SECOND / 4) || (frame % FRAMES_PER_SECOND == FRAMES_PER_SECOND / 4 * 3))
			{
				if(temp % 29 < 28)
				{
					matter[temp % 29].activate();
				}
			}
			if(frame % (FRAMES_PER_SECOND * 3) == 0)
			{
				if(temp % 16 < 4)
					for(int i = 7 * (temp % 16); i < 7 * (temp % 16 + 1 ); i ++)
						matter[i].activate();
				else if(temp % 16 < 8)
				{
					tempf = frame;
					a = true;
					n = temp % 16 - 4;
				}
				else if(temp % 16 < 12)
				{
					tempf = frame;
					b = true;
					n = temp % 16 - 8;
				}
			}
			if(a == true)
			{
				if((frame - tempf) % 4 == 0)
				{
					if((frame - tempf) / 4 <= 6)
						matter[n * 7 + (frame - tempf) / 4].activate();
					else
						a = false;
				}
			}
			if(b == true)
			{
				if((frame - tempf) % 4 == 0)
				{
					if((frame - tempf) / 4 <= 6)
						matter[n * 7 + (6 - (frame - tempf) / 4)].activate();
					else
						b = false;
				}
			}
		}
		else
		{
			if(temp % 100 < 28)
			{
				matter[temp % 100].activate();
			}
		}
		//特殊球
		if(frame % (5 * FRAMES_PER_SECOND) == FRAMES_PER_SECOND / 2 * 5)
		{
			int placeX = temp % (SCREEN_W - THING_W);
			if(left <= 45 && left > 30 && count == 0)
				scount = 9;
			else if(left <= 30 && left > 15)
			{
				if(count == 0)
					scount = 7;
				else if(count == 1)
					scount = 9;
			}
			else if(left <= 15 && left > 0)
			{
				if(count == 0)
					scount = 5;
				else if(count == 1)
					scount = 7;
				else if(count == 2)
					scount = 9;
			}
			else
				scount = 12;
			if(temp % scount == 0)
			{
				if(Crazy.getS() == false)
				{
					appear_mus.play();
					count ++;
					Crazy.set(placeX, -THING_H);
					Crazy.activate();
				}
			}
			else if(temp % scount == 1)
			{
				if(Slow.getS() == false)
				{
					appear_mus.play();
					count ++;
					Slow.set(placeX, -THING_H);
					Slow.activate();
				}
			}
			else if(temp % scount == 2)
			{
				if(Twice.getS() == false)
				{
					appear_mus.play();
					count ++;
					Twice.set(placeX, -THING_H);
					Twice.activate();
				}
			}
		}

		if(slow == false)
			frame_ps = FRAMES_PER_SECOND;
		else
			frame_ps = FRAMES_PER_SECOND/2;

		//球特效持续
		if(crazy == true)
		{
			if(crazytime >= left + 6)
				crazy = false;
		}
		if(slow == true)
		{
			if(slowtime >= left + 8)
			{
				slow = false;
				slow_end_mus.play();
			}
		}
		if(twice == true)
		{
			if(twicetime >= left + 8)
				twice = false;
		}

		//球移动显示
		hero.move();
		hero.show();
		Crazy.move();
		Crazy.show();
		Slow.move();
		Slow.show();
		Twice.move();
		Twice.show();

		for(int i = 0;i < 28; i++)
		{
			matter[i].move();
			matter[i].show();
			//计分
			if(hits == 0)
				lasthitframe = frame;
			if(frame - lasthitframe < FRAMES_PER_SECOND) 
			{
				if( Hit(hero, matter[i]) )
				{
					matter[i].reset();
					if(twice == false)
					{
						if(hits < 20)
							Score.addpoint(1);
						else if(hits < 30)
							Score.addpoint(2);
						else if(hits < 40)
							Score.addpoint(3);
						else
							Score.addpoint(4);
					}
					else
					{
						if(hits < 20)
							Score.addpoint(2);
						else if(hits < 30)
							Score.addpoint(4);
						else if(hits < 40)
							Score.addpoint(6);
						else
							Score.addpoint(8);
					}
					hits ++;
					if(hits == 20 && level == 0)
					{
						level1_mus.play();
						level ++;
					}
					else if(hits == 30 && level == 1)
					{
						level2_mus.play();
						level ++;
					}
					else if(hits == 40 && level == 2)
					{
						level3_mus.play();
						level ++;
					}
					if(hits >= 3)
					{
						Hits.setMessage(int_to_string(hits) + "Hits");
						if(hits < 20)
							Hits.setColor(255, 174, 201);
						else if(hits < 30)
							Hits.setColor(255, 255, 0);
						else if(hits < 40)
							Hits.setColor(255, 128, 0);
						else
							Hits.setColor(255, 0, 0);

					}
					lasthitframe = frame;
				}
			}
			else
			{			
				if(hits >= 3)
				{
					thits = hits;
					c = true;
					tempff = frame;				
				}		
				hits = 0;
				level = 0;
			}
		}
		if(c == true)
		{

			if(tempff + thits > frame)
			{
				if(twice == false)
					Score.addpoint(1);
				else
					Score.addpoint(2);
			}
			else
				c = false;

		}
		if( Hit(hero, Crazy) )
		{
			Crazy.reset();
			crazy = true;
			crazytime = left;
		}
		if( Hit(hero, Slow) )
		{
			Slow.reset();
			slow = true;
			slowtime = left;
			slow_start_mus.play();
		}
		if( Hit(hero, Twice) )
		{
			Twice.reset();
			twice = true;
			twicetime = left;
		}
		//底部显示
		if(hits >= 3)
			Hits.blit(550, 80);
		Score.blit_play();
		HighScore.blit(25, 55);
		if(left >= 0)
			TimeLeft.blit((SCREEN_W - TimeLeft.point() -> w) / 2 + 5, 0);
		if(slow == false)
			bg_copy.blit();
		else
			bg_slow_copy.blit();
		//暂停
		if ( Pause.effectiveClick(game_event) )
		{
			mus.stop();
			Pause.blitDown();
			switch(PauseMenu(screen))
			{
			case 0:break;
			case 1:return 2;
			case 2:return 1;
			case 3:return 3;
			default:break;
			}
			mus.play();
			Pause.blitOut();
		}
		if ( SDL_PollEvent(&game_event) != 0 )
		{
			int placeX = temp % (SCREEN_W - THING_W);
			if ( game_event.type == SDL_QUIT )
			{
				return 3;
			}
			if ( game_event.type == SDL_KEYDOWN )
			{
				if ( game_event.key.keysym.sym == SDLK_ESCAPE )
				{
					mus.stop();
					Pause.blitDown();
					switch(PauseMenu(screen))
					{
					case 0:break;
					case 1:return 2;
					case 2:return 1;
					case 3:return 3;
					default:break;
					}
					mus.play();
					Pause.blitOut();
				}
				else if ( game_event.key.keysym.sym == SDLK_1 )
				{
					if(Crazy.getS() == false)
					{
						Crazy.set(placeX, -THING_H);
						Crazy.activate();
						appear_mus.play();
					}
				}
				else if ( game_event.key.keysym.sym == SDLK_2 )
				{
					if(Slow.getS() == false)
					{
						Slow.set(placeX, -THING_H);
						Slow.activate();
						appear_mus.play();
					}
				}
				else if ( game_event.key.keysym.sym == SDLK_3 )
				{
					if(Twice.getS() == false)
					{
						Twice.set(placeX, -THING_H);
						Twice.activate();
						appear_mus.play();
					}
				}
			}
			if(game_event.type == SDLK_ESCAPE)
				return 3;
		}
		screen.flip();
		frame ++;
		if( frame % FRAMES_PER_SECOND == 0)
		{
			left --;
			if(left == 0)
			{
				for(int i = 0; i < 28; i ++)
				{
					matter[i].reset();
					matter[i].stop();
				}
			}
			else if(left < 0)
			{
				if(c == false)
				{
					//游戏结束
					mus.stop();
					Score.blit_end();
					return GameEnd(screen, Score);	
				}

			}
		}
		if( fps.get_ticks() < 1000 / frame_ps )
		{
			SDL_Delay( ( 1000 / frame_ps ) - fps.get_ticks() );
		}
	}

}

int GameEnd(const ScreenSurface& screen, ScoreBoard& score)
{
	MusicSound mus(gameend_b_mus);
	mus.play();
	int high;
	std::fstream highscore;
	highscore.open( "HighScore.dat", std::ios::out|std::ios::in|std::ios::binary);
	highscore.read((char *)&high, sizeof(int));
	StringData text("GameEnd");
	PictureSurface bg(gameend_bg_img, screen);
	bg.blit();
	TextSurface gameover(text[0], screen, 255, 0, 0, 80);
	gameover.blit((SCREEN_W - gameover.point()->w) / 2, 20);
	TextSurface your(text[1], screen, 255, 255, 255, 40);
	your.blit((SCREEN_W - your.point()->w) / 2, 150);
	if(high < score.getScore())
	{
		break_mus.play();
		high = score.getScore();
		highscore.seekp(std::ios::beg);
		highscore.write((char *)&high, sizeof(int));
		TextSurface congratulation(text[4], screen, 0, 0, 0, 50);
		PictureSurface Congratulations(gameend_congratulations_img, screen);
		Congratulations.colorKey(33, 88, 50);
		Congratulations.blit((SCREEN_W - Congratulations.point()->w) / 2, 305);
		congratulation.blit((SCREEN_W - congratulation.point()->w) / 2, 330);
	}
	highscore.close();
	score.setsize(80);
	score.setup((SCREEN_W - score.point()->w) / 2 + 18, 230);
	score.setcolor(255, 128, 0);
	score.setfont("./fonts/bluebold.ttf");
	score.blit_end();
	Button B[2]=
	{
		Button(gameend_b_out_img, gameend_b_over_img, screen),
		Button(gameend_b_out_img, gameend_b_over_img, screen)
	};
	TextSurface again_out(text[2], screen, 207, 169, 114);
	TextSurface again_over(text[2], screen, 0, 26, 0);
	TextSurface quit_out(text[3], screen, 207, 169, 114);
	TextSurface quit_over(text[3], screen, 0, 26, 0);
	B[0].addText(again_out, again_over);
	B[1].addText(quit_out, quit_over);
	B[0].setup(SCREEN_W / 3 - B[0].point() -> w / 2, 400, 1);
	B[1].setup(SCREEN_W / 3 * 2 - B[0].point() -> w / 2, 400, 1);
	B[0].blitOut();
	B[1].blitOut();
	screen.flip();
	SDL_Event game_event;
	while(1)
	{

		while ( SDL_PollEvent(&game_event) != 0 )
		{
			bg.blit(SCREEN_W / 3 - B[0].point() -> w / 2, 400, SCREEN_W / 3 - B[0].point() -> w / 2, 400, 400, B[0].point() -> h);
			if(B[0].effectiveClick(game_event))
				return 2;
			else if(B[1].effectiveClick(game_event))
				return 1;
			if ( game_event.type == SDL_QUIT )
			{
				return 3;
			}
		}
		screen.flip();
		SDL_Delay(10);
	}

}

int PauseMenu(const ScreenSurface& screen)
{
	StringData text("PauseMenu");
	SDL_Event game_event;
	Button B[3] = 
	{
		Button(pausemenu_b_out_img, pausemenu_b_over_img, screen),
		Button(pausemenu_b_out_img, pausemenu_b_over_img, screen),
		Button(pausemenu_b_out_img, pausemenu_b_over_img, screen)
	};
	TextSurface return_game_out(text[0], screen, 0, 160, 233);
	TextSurface return_game_over(text[0], screen, 255, 255, 0);
	TextSurface retry_game_out(text[1], screen, 0, 160, 233);
	TextSurface retry_game_over(text[1], screen, 255, 255, 0);
	TextSurface quit_game_out(text[2], screen, 0, 160, 233);
	TextSurface quit_game_over(text[2], screen, 255, 255, 0);
	B[0].addText(return_game_out, return_game_over);
	B[1].addText(retry_game_out, retry_game_over);
	B[2].addText(quit_game_out, quit_game_over);
	B[0].setup((SCREEN_W - B[0].point() -> w) / 2, (SCREEN_H - B[0].point() -> h) / 2 - 100, 1);
	B[1].setup((SCREEN_W - B[0].point() -> w) / 2, (SCREEN_H - B[0].point() -> h) / 2, 1);
	B[2].setup((SCREEN_W - B[0].point() -> w) / 2, (SCREEN_H - B[0].point() -> h) / 2 + 100, 1);
	B[0].blitOut();
	B[1].blitOut();
	B[2].blitOut();
	screen.flip();
	while(1)
	{
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			if ( game_event.type == SDL_KEYDOWN )
			{
				if ( game_event.key.keysym.sym == SDLK_ESCAPE )
					return 0;
			}
			if(B[0].effectiveClick(game_event))
			{
				return 0;
			}
			else if(B[1].effectiveClick(game_event))
				return 1;
			else if(B[2].effectiveClick(game_event))
				return 2;
			if ( game_event.type == SDL_QUIT )
			{
				return 3;
			}
		}
		SDL_Delay(10);
		screen.flip();
	}
}

bool Hit( Ball& matter_h, Thing& matter_t)
{
	int ballX = matter_h.getX() + BALL_W/2;
	int ballY = matter_h.getY() + BALL_H/2;
	int ballR = BALL_W/2;
	int thingX = matter_t.getX() + THING_W/2;
	int thingY = matter_t.getY() + THING_H/2;
	int thingR = THING_W/2;

	if(sqrt(double((ballX - thingX) * (ballX - thingX) + (ballY - thingY) * (ballY - thingY))) <= (ballR + thingR))
	{
		hit_mus.play();
		return true;
	}
	else
		return false;
}

bool Show3s(const ScreenSurface& screen)
{	
	int init_size = 40;
	int size = init_size;
	int t = 0;
	SDL_Event game_event;

	PictureSurface bg(game_bg_img,screen);
	TextSurface threes("3", screen, 255, 255, 0, size);
	Timer count;

	count.start();
	bg.blit();
	screen.flip();
	while(1)
	{
		if(size >= 100)
		{
			size = 40;
			t++;
			if(t < 3)
			{
				threes.setMessage(int_to_string(3-t));
			}
			else if(t == 3)
			{
				threes.setMessage("GO");
			}
			else
				return false;
		}
		else
		{
			size += 2;
			threes.setSize(size);
		}
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			if ( game_event.type == SDLK_ESCAPE )
				return true;
		}
		bg.blit();
		threes.blit();
		screen.flip();
		SDL_Delay(10);
	}
}

bool Help(const ScreenSurface& screen)
{
	PictureSurface bg(help_bg_img, screen);
	bg.blit();
	StringData text("Help");
	PictureSurface blackball(hero_img, screen);
	PictureSurface yellowball(thing_img, screen);
	PictureSurface redball(crazy_img, screen);
	PictureSurface blueball(slow_img, screen);
	PictureSurface purpleball(twice_img, screen);
	blackball.colorKey(67, 102, 106);
	yellowball.colorKey(65, 98, 103);
	redball.colorKey(65, 98, 103);
	blueball.colorKey(65, 98, 103);
	purpleball.colorKey(65, 98, 103);
	PictureSurface A(help_A_img, screen);
	PictureSurface D(help_D_img, screen);
	PictureSurface L(help_L_img, screen);
	PictureSurface R(help_R_img, screen);
	A.colorKey(8, 1, 0);
	D.colorKey(8, 1, 0);
	L.colorKey(8, 1, 0);
	R.colorKey(8, 1, 0);

	A.blit(240, 80);
	L.blit(290, 80);
	D.blit(450, 80);
	R.blit(500, 80);
	blackball.blit(150, 130);
	yellowball.blit(160, 200);
	redball.blit(160, 260);
	blueball.blit(160, 320);
	purpleball.blit(160, 380);

	TextSurface whole(text[0], screen);
	TextSurface black(text[1], screen);
	TextSurface yellow(text[2], screen);
	TextSurface red(text[3], screen);
	TextSurface blue(text[4], screen);
	TextSurface purple(text[5], screen);

	whole.setSize(40);
	whole.blit(140, 80);
	black.blit(220, 150);
	yellow.blit(220, 210);
	red.blit(220, 270);
	blue.blit(220, 330);
	purple.blit(220, 390);

	Button Return(help_return_out_img, help_return_over_img, screen);
	Return.colorKey(8, 1, 0);
	Return.setup( 590, 370, 1);
	Return.blitOut();
	screen.flip();
	SDL_Event game_event;

	while(1)
	{
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			if ( game_event.type == SDLK_ESCAPE )
				return true;
			if ( Return.effectiveClick(game_event) )
				return false;
		}
		SDL_Delay(10);
		screen.flip();
	}
}

bool LogoShow(const ScreenSurface& screen)
{
	SDL_Event game_event;
	PictureSurface logo(logo_img, screen);
	logo.colorKey(255, 255, 255);
	for(int i = 0; i < 256; i += 2)
	{
		screen.fillColor(i, i, i);
		logo.blit();
		screen.flip();
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			if ( game_event.type == SDLK_ESCAPE )
				return true;
		}
		SDL_Delay(10);
	}
	for(int i = 255; i >= 0; i -= 2)
	{
		screen.fillColor(i, i, i);
		logo.blit();
		screen.flip();
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			if ( game_event.type == SDLK_ESCAPE )
				return true;
		}
		SDL_Delay(10);
	}
	return false;
}
