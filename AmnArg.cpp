#include "AmnArg.h"


//class AmnArg
AmnArg::AmnArg(int begin_x, int begin_y, int end_x, int end_y, const std::string& bg_filename, const std::string& s_filename, const ScreenSurface& _screen):
kind(_kind), beginX(begin_x), initX(begin_x), beginY(begin_y), initY(begin_y), endX(end_x), endY(end_y), bg_FileName(bg_filename), s_FileName(s_filename),screen(_screen),Amn(NULL)
{}


SDL_Thread* AmnArg::createThrd()
{
	if(kind == 1)
    return SDL_CreateThread(amn_v, (void*)this);
	if(kind == 2)
	return SDL_CreateThread(amn_g, (void*)this);
	if(kind == 3)
	return SDL_CreateThread(amn_control, (void*)this);
}

void AmnArg::start()
{
	if(kind == 1)
    Amn = SDL_CreateThread(amn_v, (void*)this);
	if(kind == 2)
	Amn = SDL_CreateThread(amn_g, (void*)this);
	if(kind == 3)
	Amn = SDL_CreateThread(amn_control, (void*)this);
}

void AmnArg::stop()
{
	lastX = beginX;
	lastY = beginY;
	SDL_KillThread(Amn);
	Amn = NULL;
}

void AmnArg::goon()
{
	set(lastX, lastY);
	if(kind == 1)
    Amn = SDL_CreateThread(amn_v, (void*)this);
	if(kind == 2)
	Amn = SDL_CreateThread(amn_g, (void*)this);
	if(kind == 3)
	Amn = SDL_CreateThread(amn_control, (void*)this);
}

void AmnArg::show() const
{
    std::cout << "Now x at: " << beginX << std::endl;
	std::cout << "Now y at:"  << beginY << std::endl;
}

void AmnArg::reset()
{
	beginX = initX;
	beginY = initY;
}

void AmnArg::set(int x,int y)
{
    beginX = x;
	beginY = y;
}

int AmnArg::getX() const
{
	return beginX;
}

int AmnArg::getY() const
{
	return beginY;
}

int AmnArg::amn_v(void* pThat)
{
    AmnArg* pData = (AmnArg*)pThat;
	PictureSurface stand(pData->s_FileName, pData->screen);
    stand.colorKey();
	PictureSurface bg(pData->bg_FileName, pData->screen);

    const int SPEED_CTRL = 300;
    int speedX = (pData->endX - pData->beginX) / SPEED_CTRL;
    int speedY = (pData->endY - pData->beginY) / SPEED_CTRL;

    for ( int i = 0; i < SPEED_CTRL; i++ ){
		bg.blit(pData->beginX, pData->beginY, pData->beginX, pData->beginY, stand.point()->w, stand.point()->h, 2, 2);
        pData->beginX += speedX;
        pData->beginY += speedY;
        stand.blit(pData->beginX, pData->beginY);
        pData->screen.flip();
        SDL_Delay(10);
    }

    return 0;
}

int AmnArg::amn_g(void* pThat)
{
    AmnArg* pData = (AmnArg*)pThat;
    PictureSurface stand(pData->s_FileName, pData->screen);
    stand.colorKey();
    PictureSurface bg(pData->bg_FileName, pData->screen);

    const int SPEED_CTRL = 300;
	const int g=1;
    int speedX = (pData->endX - pData->beginX) / SPEED_CTRL;
    int speedY = 0;

    for ( int i = 0; i < SPEED_CTRL; i++ ){
		bg.blit(pData->beginX, pData->beginY, pData->beginX, pData->beginY, stand.point()->w, stand.point()->h, 2, 2);
        pData->beginX += speedX;
		speedY+=g;
        pData->beginY += speedY;
		if(pData->beginY>450)
		{
			pData->beginY=450;
			speedY=-speedY;
		}
        stand.blit(pData->beginX, pData->beginY);
        pData->screen.flip();
        SDL_Delay(10);
    }

    return 0;
}



int AmnArg::amn_control(void* pThat)
{
	Uint8* keys;
	AmnArg* pData = (AmnArg*)pThat;
    PictureSurface stand(pData->s_FileName, pData->screen);
    stand.colorKey();
    PictureSurface bg(pData->bg_FileName, pData->screen);
	int g = 1;
    int speedX = 0;
    int speedY = 0;
	bool over = false;
    while(over == false)
	{
		bg.blit(pData->beginX, pData->beginY, pData->beginX, pData->beginY, stand.point()->w, stand.point()->h, 2, 2);
		keys = SDL_GetKeyState(0);
		if ( keys[SDLK_LEFT]|| keys[SDLK_a] )
		{
            speedX = -1;
        }
		else
		{
			if ( keys[SDLK_RIGHT]|| keys[SDLK_d] )
			{
				speedX = 1;
			}
			else
			speedX = 0;
		}
        pData->beginX += speedX;
		speedY+=g;
        pData->beginY += speedY;
		if(pData->beginY>450)
		{
			pData->beginY=450;
			speedY=-speedY;
		}
		if(pData->beginX<0)
			pData->beginX=0;
		if(pData->beginX>576)
			pData->beginX=576;
        stand.blit(pData->beginX, pData->beginY);
        pData->screen.flip();
        SDL_Delay(10);
    }

    return 0;
}


//class Strip


Strip::Strip(int begin_x, int begin_y, int end_x, int end_y, int l, const std::string& bg_filename, const std::string& s_filename, const std::string& sbg_filename, const ScreenSurface& _screen):
AmnArg(begin_x, begin_y, end_x, end_y, bg_filename, s_filename, _screen),sbg_FileName(sbg_filename),length(l),init_l(l)
{}

SDL_Thread* Strip::createThrd_loading()
{
    return SDL_CreateThread(amn_loading, (void*)this);
}

SDL_Thread* Strip::createThrd_time()
{
    return SDL_CreateThread(amn_time, (void*)this);
}

void Strip::show() const
{
	std::cout<<"Now length is"<<std::endl;
}

int Strip::getLength() const
{
	return length;
}

void Strip::set(int l)
{
	length = l;
}

void Strip::reset()
{
	beginX = initX;
	beginY = initY;
}

int Strip::amn_loading(void* pThat)
{
	Strip* pData = (Strip*)pThat;
    PictureSurface Time_bg(pData->sbg_FileName, pData->screen);
	PictureSurface Time_real(pData->s_FileName, pData->screen);
	const int SPEED_CTRL = 390;
	int speed = Time_real.point()->w / SPEED_CTRL;
	int deltaX = (Time_bg.point()->w - Time_real.point()->w)/2;
	int deltaY = (Time_bg.point()->h - Time_real.point()->h)/2;
	Time_bg.blit(pData->beginX, pData->beginY,0 , 0 , Time_bg.point()->w, Time_bg.point()->h, 0, 0);
	Time_real.blit(pData->beginX + deltaX, pData->beginY + deltaY,0 , 0 , pData->length, Time_real.point()->h, 0, 0);
	for(int i = 0; i < SPEED_CTRL;i++)
	{
		pData->length += speed;
		Time_real.blit(pData->beginX + pData->length + deltaX, pData->beginY + deltaY, pData->length , 0 ,speed , Time_real.point()->h, 0, 0);
		pData->screen.flip();
		SDL_Delay(100);
	}
	return 0;
}

int Strip::amn_time(void* pThat)
{
	Strip* pData = (Strip*)pThat;
    PictureSurface Time_bg(pData->sbg_FileName, pData->screen);
	PictureSurface Time_real(pData->s_FileName, pData->screen);

	const int SPEED_CTRL = 390;
	int speed = Time_real.point()->w / SPEED_CTRL;
	int deltaX = (Time_bg.point()->w - Time_real.point()->w)/2;
	int deltaY = (Time_bg.point()->h - Time_real.point()->h)/2;
	Time_bg.blit(pData->beginX, pData->beginY,0 , 0 , Time_bg.point()->w, Time_bg.point()->h, 0, 0);
	Time_real.blit(pData->beginX + deltaX, pData->beginY + deltaY,0 , 0 , pData->length, Time_real.point()->h, 0, 0);
	for(int i = 0; i < SPEED_CTRL;i++)
	{
		pData->length -= speed;
		Time_bg.blit(pData->beginX + pData->length + deltaX, pData->beginY + deltaY, pData->length + deltaX , deltaY ,speed , Time_real.point()->h, 0, 0);
		pData->screen.flip();
		SDL_Delay(100);
	}
	return 0;
}