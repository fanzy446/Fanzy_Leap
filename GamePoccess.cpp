#include"GamePoccess.h"
int GamePoccess(const ScreenSurface& screen)
{
	SDL_Event game_event;
	int ball_at_x = 320;
	int ball_at_y = 50;
	//计分板初始化
	bool GameOver=false;
	PictureSurface bg("h3_bg.png",screen);
	ButtonPlus Pause("h3_yes_over.png","h3_yes_over.png","h3_yes_over.png",screen);
	//3秒计时，音效
	/*Begin();*/
	//音乐
	//计分板显示
	Pause.blitOut();
	std::string bg_img = "./images/ h3_bg.png";
	std::string sbg_img = "./images/loading_bg.png";
	std::string h_s_img = "./images/loading_img.png";
	std::string c_s_img = "./images/loading_img.png";
	std::string s_s_img = "./images/loading_img.png";
	AmnArg Ball(ball_at_x-BALL_W, ball_at_y, 0, 0, bg_img, h_s_img, screen);
	Strip Time(0, 0, 0, 0, TIME_W, bg_img, sbg_img, c_s_img, screen);
	SDL_Thread* Hero=Ball.createThrd_control();
	SDL_Thread* RestTime=Time.createThrd_time();
	int BeginX = -BALL_W;
	int BeginY = TIME_H + 20;
	int EndX = SCREEN_W;
	int EndY = TIME_H + 20;
	int n = 0;
	AmnArg Common[20]=
	{
		AmnArg(BeginX, BeginY, EndX, EndY, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H, EndX, EndY+THING_H, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*2, EndX, EndY+THING_H*2, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*3, EndX, EndY+THING_H*3, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*4, EndX, EndY+THING_H*4, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*5, EndX, EndY+THING_H*5, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*6, EndX, EndY+THING_H*6, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*7, EndX, EndY+THING_H*7, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*8, EndX, EndY+THING_H*8, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY+THING_H*9, EndX, EndY+THING_H*9, bg_img, c_s_img, screen),
		AmnArg(BeginX, BeginY, EndX, EndY, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H, BeginX, BeginY+THING_H, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*2, BeginX, BeginY+THING_H*2, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*3, BeginX, BeginY+THING_H*3, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*4, BeginX, BeginY+THING_H*4, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*5, BeginX, BeginY+THING_H*5, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*6, BeginX, BeginY+THING_H*6, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*7, BeginX, BeginY+THING_H*7, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*8, BeginX, BeginY+THING_H*8, bg_img, c_s_img, screen),
		AmnArg(EndX, EndY+THING_H*9, BeginX, BeginY+THING_H*9, bg_img, c_s_img, screen),
	};
	SDL_Thread* C_thing[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	bool Double = false;
	bool Stop = false;
	bool Slow = false;
	bool Boom = false;
	bool Free = false;

	srand(time(0));

	while(GameOver==false)
	{
		n = rand()%30;
		switch(n)
		{
			case 0:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 1:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 2:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 3:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 4:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 5:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 6:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 7:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 8:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 9:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 10:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 11:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 12:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 13:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 14:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 15:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 16:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 17:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 18:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 19:if(C_thing[n] == NULL)C_thing[n] = Common[n].createThrd_v();break;
			case 20:if(C_thing[0] == NULL)C_thing[0] = Common[0].createThrd_g();break;
			case 21:if(C_thing[1] == NULL)C_thing[1] = Common[1].createThrd_g();break;
			case 22:if(C_thing[2] == NULL)C_thing[2] = Common[2].createThrd_g();break;
			case 23:if(C_thing[3] == NULL)C_thing[3] = Common[3].createThrd_g();break;
			case 24:if(C_thing[4] == NULL)C_thing[4] = Common[4].createThrd_g();break;
			case 25:if(C_thing[10] == NULL)C_thing[10] = Common[10].createThrd_g();break;
			case 26:if(C_thing[11] == NULL)C_thing[11] = Common[11].createThrd_g();break;
			case 27:if(C_thing[12] == NULL)C_thing[12] = Common[12].createThrd_g();break;
			case 28:if(C_thing[13] == NULL)C_thing[13] = Common[13].createThrd_g();break;
			case 29:if(C_thing[14] == NULL)C_thing[14] = Common[14].createThrd_g();break;
			default: ErrorInfo("物品丢出失败");break;
		}
		//int t = 0;
		//if(n>=0||n<=19)
		//	t = n;
		//else if(n<=24)
		//	t = n-20;
		//else if(n<=29)
		//	t = n-15;
		//else
		//	ErrorInfo("物品数据错误");
		for(int i = 0; i < 20; i++)
		{
			if(Hit(Ball, Common[i]))
			{
				//音效
				SDL_KillThread(C_thing[i]);
				C_thing[i] = NULL;
				Common[i].reset();
				//加分并显示
				
			}
		}
		if(Pause.effectiveClick(game_event))
		{
			
			int time = Time.getLength();
			SDL_KillThread(RestTime);
			//菜单显示及响应
			Time.set(time);
			RestTime = Time.createThrd_time();
		}
		if(Time.getLength() == TIME_W)
		{
			GameOver = true;
			//结束界面及选项
		}
	}
}


bool Hit(const AmnArg& matter_h,const AmnArg& matter_t)
{
	if(matter_h.getX() - matter_t.getX() < 0)
	{
		if(matter_h.getY() - matter_t.getY() < 0)
		{
			if(matter_t.getY() - matter_h.getY() <= BALL_H && matter_t.getX() - matter_h.getX() <= BALL_W)
				return true;
			else
				return false;
		}
		else
		{
			if(matter_h.getY() - matter_t.getY() <= THING_H && matter_t.getX() - matter_h.getX() <= BALL_W)
				return true;
			else
				return false;
		}
	}
	else
	{
		if(matter_h.getY() - matter_t.getY() < 0)
		{
			if(matter_t.getY() - matter_h.getY() <= BALL_H && matter_h.getX() - matter_t.getX() <= THING_W)
				return true;
			else
				return false;
		}
		else
		{
			if(matter_h.getY() - matter_t.getY() <= THING_H && matter_h.getX() - matter_t.getX() <= THING_W)
				return true;
			else
				return false;
		}
	}
}
		
