#include"game_loop.h"


const std::string startmenu_bg_img = "./images/h3_bg.png";
const std::string startmenu_b_out_img = "./images/begin_button_off.png";
const std::string startmenu_b_over_img = "./images/begin_button_over.png";
const std::string game_bg_img = "./images/h3_bg.png";
const std::string game_pause_out_img = "./images/h3_yes_off.png";
const std::string game_pause_over_img = "./images/h3_yes_over.png";
const std::string hero_img = "thing1.png";
const std::string thing_img = "thing2.png";
const std::string pausemenu_bg_img = "./images/dialog_bg.png";
const std::string pausemenu_b_out_img = "./images/begin_button_off.png";
const std::string pausemenu_b_over_img = "./images/begin_button_over.png";
const int FRAMES_PER_SECOND = 20;



int game(void* data)
{

	//Create a SDL screen.
	const Uint32 SCREEN_FLAGS = 0; //SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE
	const std::string WINDOW_NAME = "Leap      by Fanzy";
	ScreenSurface screen(SCREEN_W, SCREEN_H, WINDOW_NAME, 0, SCREEN_FLAGS);
	std::cout<<"窗口创建"<<std::endl;

	//music loading
	MusicSound mus("./sounds/bgMusic.mid");
	
	std::cout<<"音乐加载"<<std::endl;
	//Fanzy Logo
	//Fanzy_begin(screen);

	//main loop
	bool GameOver = false;
	int n = 1;
	while(1)
	{
		switch(n)
		{
		case 1:mus.play();n = StartMenu(screen);break;
		case 2:mus.stop();n = GamePoccess(screen);break;
		case 3:	//end_show(screen);
				//end music
				mus.stop();
				return 0;
		case 4:
				mus.stop();
				return 0;
		default:
			mus.stop();
			return -1;
		}
	}

}

int StartMenu(const ScreenSurface& screen)
{
	PictureSurface bg("./images/h3_bg.png", screen);
	bg.blit();
	Button B[2]=
	{
		Button("./images/begin_button_off.png", "./images/begin_button_over.png", screen),
		Button("./images/begin_button_off.png", "./images/begin_button_over.png", screen)
	};
	TextSurface Choice[2]=
	{
		TextSurface("Start", screen, 0xFF, 0xFF, 0xFF),
		TextSurface("Quit", screen, 0xFF, 0xFF, 0xFF)
	};
	B[0].addText(Choice[0], Choice[0]);
	B[1].addText(Choice[1], Choice[1]);
	B[0].setup(300, 200, 1);
	B[1].setup(300, 260, 1);
	B[0].blitOut();
	B[1].blitOut();
	screen.flip();
	SDL_Event game_event;
	while(1)
	{
		while ( SDL_PollEvent(&game_event) != 0 )
		{
			if(B[0].effectiveClick(game_event))
				return 2;
			if(B[1].effectiveClick(game_event))
				return 3;
		}
		screen.flip();
		SDL_Delay(10);
	}
}

int GamePoccess(const ScreenSurface& screen)
{
	SDL_Event game_event;
	bool GameOver=false;
	int frame = 0;


	PictureSurface bg(game_bg_img,screen);
	bg.blit();
	//3秒计时，音效
	/*Begin();*/
	//音乐
	//计分板显示
	ScoreBoard Score(20, 20, game_bg_img, screen);
	Score.blit_play();
	
	Button Pause("./images/h3_yes_off.png","./images/h3_yes_over.png",screen);
	Pause.setup(560, 20 ,1);
	Pause.blitOut();
	
	int frame_ps = FRAMES_PER_SECOND;
	int left = 60;
	bool crazy = false;
	int crazytime = left;
	bool slow = false;
	int slowtime = left;
	bool twice = false;
	int twicetime = left;
	int check1 = left;
	int check2 = left/3;
	int hits = 0;
	int lasthitframe = 0;
	int hitframe = 0;

	screen.flip();

	Ball hero((SCREEN_W - BALL_W)/2, 60, 15, 1, hero_img, game_bg_img, screen);
	Thing matter[28]=
	{
		Thing(1, - THING_W, 60, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, - THING_W, 120, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, - THING_W, 180, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, - THING_W, 240, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, - THING_W, 300, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, - THING_W, 360, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, - THING_W, 420, 10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 60, -10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 120, -10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 180, -10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 240, -10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 300, -10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 360, -10, 0, thing_img, game_bg_img, screen),
		Thing(1, SCREEN_W, 420, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 60, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 120, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 180, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 240, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 300, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 360, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, - THING_W, 420, 10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 60, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 120, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 180, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 240, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 300, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 360, -10, 0, thing_img, game_bg_img, screen),
		Thing(2, SCREEN_W, 420, -10, 0, thing_img, game_bg_img, screen),
	};
	Thing Crazy(3, 0, -THING_H, 0, 10, "thing3.png", game_bg_img, screen);
	Thing Slow(3, 0, -THING_H, 0, 10, "thing4.png", game_bg_img, screen);
	Thing Twice(3, 0, -THING_H, 0, 10, "thing5.png", game_bg_img, screen);
	srand(time(0));



	while(1)
	{
		//定义
		int temp = rand();
		TextSurface TimeLeft( int_to_string(left), screen, 0xFF, 0xFF, 0xFF );
		TextSurface Hits(int_to_string(hits) + "Hits", screen, 0xFF, 0xFF, 0xFF, 40);
		TimeLeft.blit(310, 20);
		Timer fps;
		fps.start();

		//球激活
		if(crazy == false)
		{
			
			if(check1 != left)
			{
				
				check1 = left;
				if(temp % 50 < 28)
				{
					matter[temp%50].activate();
				}
			}
			if(check2 != left/3)
			{
				check2 = left/3;
				if(temp % 9 < 4)
					for(int i = 7 * (temp % 9); i < 7 * (temp % 9 + 1 ); i ++)
						matter[i].activate();
			}

		}
		else
		{
			if(temp % 100 < 28)
			{
				matter[temp % 100].activate();
			}
		}

		if(frame % (1 * FRAMES_PER_SECOND) == 0)
		{
			int placeX = temp % (SCREEN_W - THING_W);
			if(temp % 12 == 0)
			{
				Crazy.set(placeX, -THING_H);
				Crazy.activate();
			}
			else if(temp % 12 == 1)
			{
				Slow.set(placeX, -THING_H);
				Slow.activate();
			}
			else if(temp % 12 == 2)
			{
				Twice.set(placeX, -THING_H);
				Twice.activate();
			}
		}

		if(slow == false)
			frame_ps = FRAMES_PER_SECOND;
		else
			frame_ps = FRAMES_PER_SECOND/2;

		//球特效持续
		if(crazy == true)
		{
			if(crazytime >= left + 5)
				crazy = false;
		}
		if(slow == true)
		{
			if(slowtime >= left + 8)
				slow = false;
		}
		if(twice == true)
		{
			if(twicetime >= left + 10)
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
			if( Hit(hero, matter[i]) )
			{
				matter[i].reset();
				if(hits == 0)
					lasthitframe = frame;
				if(twice == false)
						Score.addpoint(1);
					else
						Score.addpoint(2);
				if(frame - lasthitframe < FRAMES_PER_SECOND) 
				{
					hits ++;
					if(hits >= 3)
					{
						Hits.setmessage(int_to_string(hits) + "Hits");
						bg.blit(500, 60, 500, 60, Hits.point()->w, Hits.point()->h);
						Hits.blit(500, 60);
					}
					lasthitframe = frame;
				}
				else
				{
					if(hits >= 3)
					{
					if(twice == false)
						Score.addpoint(hits);
					else
						Score.addpoint(hits * 2);
					bg.blit(500, 60, 500, 60, Hits.point()->w, Hits.point()->h);
					}
					hits = 0;
					
				}		
			}
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
		}
		if( Hit(hero, Twice) )
		{
			Twice.reset();
			twice = true;
			twicetime = left;
		}
		if ( Pause.effectiveClick(game_event) )
		{
			hero.stop();
			for(int i = 0;i <14;i ++)
				matter[i].stop();
			Pause.blitDown();
			switch(PauseMenu(screen))
			{
			case 1:
			case 2:return 1;
			case 3:
			case 0:break;
			default:break;
			}
			bg.blit();
			hero.goon();
			for(int i = 0;i <14;i ++)
				matter[i].goon();
			Pause.blitOut();
		}
		if ( SDL_PollEvent(&game_event) != 0 )
		{
			

			if ( game_event.type == SDL_QUIT )
			{
				return 3;
			}
			if ( game_event.type == SDL_KEYDOWN )
			{
				if ( game_event.key.keysym.sym == SDLK_ESCAPE )
				{
					hero.stop();
					for(int i = 0;i <14;i ++)
						matter[i].stop();
					Pause.blitDown();
					switch(PauseMenu(screen))
					{
					case 1:
					case 2:return 1;
					case 3:
					case 0:break;
					default:break;
					}
					bg.blit();
					hero.goon();
					for(int i = 0;i <14;i ++)
						matter[i].goon();
					Pause.blitOut();
				}
			}
		}
		if(hits >= 3)
			Hits.blit(500, 60);
		Score.blit_play();
		screen.flip();
		frame ++;
		if( frame % frame_ps == 0)
		{
			left --;
			bg.blit(310, 10, 310, 10, TimeLeft.point()->w, TimeLeft.point()->h + 3);
			if(left == 0)
				return 3;			
		}
		if( fps.get_ticks() < 1000 / frame_ps )
		{
			SDL_Delay( ( 1000 / frame_ps ) - fps.get_ticks() );
		}
	}

}

int PauseMenu(const ScreenSurface& screen)
{
	SDL_Event game_event;
	PictureSurface GamePause("./images/dialog_bg.png", screen);
	GamePause.blit();
	Button B[2] = 
	{
		Button("./images/begin_button_off.png", "./images/begin_button_over.png", screen),
		Button("./images/begin_button_off.png", "./images/begin_button_over.png", screen)
	};
	TextSurface return_game("Return", screen, 0xFF, 0xFF, 0xFF);
	TextSurface quit_game("Quit", screen, 0xFF, 0xFF, 0xFF);
	B[0].addText(return_game, return_game);
	B[1].addText(quit_game, quit_game);
	B[0].setup(300, 200, 1);
	B[1].setup(300, 270, 1);
	B[0].blitOut();
	B[1].blitOut();
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
				return 0;
			if(B[1].effectiveClick(game_event))
				return 2;
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
		return true;
	else
		return false;
}
