#include "SurfaceClass.h"

//*****************************************
//class ScreenSurface

int ScreenSurface::screenNum = 0;

ScreenSurface::ScreenSurface():
width(640), height(480), bpp(32), flags(0), windowName("NULL")
{
	if ( screenNum > 0 )
		throw ErrorInfo("DONOT create more than ONE screen!");
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
		throw ErrorInfo(SDL_GetError());
	pScreen = SDL_SetVideoMode(width, height, bpp, flags);
	screenNum++;
}

ScreenSurface::ScreenSurface(int w, int h, const std::string& window_name, const std::string& icon_name, int b, Uint32 f):
width(w), height(h), bpp(b), flags(f)
{
	if ( screenNum > 0 )
		throw ErrorInfo("DONOT create more than ONE screen!");
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
		throw ErrorInfo(SDL_GetError());
	pScreen = SDL_SetVideoMode(width, height, bpp, flags);
	screenNum++;



	if ( window_name != "NULL" ) 
	{
		windowName = window_name;
		SDL_WM_SetCaption(windowName.c_str(), 0);
	}
	else
		windowName = "NULL";
	if ( icon_name != "NULL" ) 
	{
		iconName = icon_name;
		SDL_WM_SetIcon(IMG_Load(iconName.c_str()), NULL);
	}
	else
		iconName = "NULL";

}

ScreenSurface::~ScreenSurface()
{
	SDL_Quit();
}

//***

SDL_Surface* ScreenSurface::point() const
{
	return pScreen;
}

void ScreenSurface::flip() const
{
	if ( SDL_Flip(pScreen) < 0 )
		throw ErrorInfo(SDL_GetError());
}


void ScreenSurface::fillColor(Uint8 r, Uint8 g, Uint8 b) const
{
	if ( SDL_FillRect(pScreen, 0, SDL_MapRGB(pScreen->format, r, g, b)) < 0 )
		throw ErrorInfo(SDL_GetError());
}

//************************************



//************************************
//class BaseSurface

//protected
//public
BaseSurface::BaseSurface():
pScreen(0), pSurface(0)
{}

BaseSurface::BaseSurface(const BaseSurface& copy):
pScreen(copy.pScreen)
{
	pSurface = SDL_ConvertSurface(copy.pSurface, copy.pSurface->format, SDL_SWSURFACE);
	if ( pSurface == 0 )
		throw ErrorInfo(SDL_GetError());
}

BaseSurface::~BaseSurface()
{
	SDL_FreeSurface(pSurface);
}

BaseSurface& BaseSurface::operator=(const BaseSurface& copy)
{
	SDL_FreeSurface(pSurface);
	pSurface = SDL_ConvertSurface(copy.pSurface, copy.pSurface->format, SDL_SWSURFACE);
	if ( pSurface == 0 )
		throw ErrorInfo(SDL_GetError());
	return *this;
}

//***

SDL_Surface* BaseSurface::point() const
{
	return pSurface;
}

//***

void BaseSurface::blit() const
{
	const int SRC_W = pSurface->w;
	const int SRC_H = pSurface->h;
	const int DST_W = pScreen->w;
	const int DST_H = pScreen->h;

	SDL_Rect offset1;
	offset1.x = ( DST_W - SRC_W ) / 2;
	offset1.y = ( DST_H - SRC_H ) / 2;
	if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset1) < 0 )
		throw ErrorInfo(SDL_GetError());
}

void BaseSurface::blit(int any_num) const
{
	const int SRC_H = pSurface->h;
	const int DST_H = pScreen->h;
	const int SRC_W = pSurface->w;
	const int DST_W = pScreen->w;
	switch(any_num)
	{
		//左上角
	case 1:
		if ( SDL_BlitSurface(pSurface, 0, pScreen, 0) < 0 )
			throw ErrorInfo(SDL_GetError());
		break;

		//顶部中间
	case 2:
		SDL_Rect offset2;
		offset2.x = ( DST_W - SRC_W ) / 2;
		offset2.y = 0;
		if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset2) < 0 )
			throw ErrorInfo(SDL_GetError());
		break;

		//右上角
	case 3:
		SDL_Rect offset3;
		offset3.x = DST_W - SRC_W;
		offset3.y = 0;
		if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset3) < 0 )
			throw ErrorInfo(SDL_GetError());
		break;

		//左部中间
	case 4:
		SDL_Rect offset4;
		offset4.x = 0;
		offset4.y = ( DST_H - SRC_H ) / 2;
		if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset4) < 0 )
			throw ErrorInfo(SDL_GetError());
		break;
	default:
		ErrorInfo("wrong number");
	}
}

void BaseSurface::blit(int at_x, int at_y) const
{
	SDL_Rect offset;
	offset.x = at_x;
	offset.y = at_y;

	if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset) < 0 )
		throw ErrorInfo(SDL_GetError());
}

void BaseSurface::blit(int at_x, int at_y,
	int from_x, int from_y, int w, int h,
	int delta_x, int delta_y) const
{
	SDL_Rect offset;
	offset.x = at_x - delta_x;
	offset.y = at_y - delta_y;

	SDL_Rect dest;
	dest.x = from_x - delta_x;
	dest.y = from_y - delta_y;
	dest.w = w + delta_x*2;
	dest.h = h + delta_y*2;

	if ( SDL_BlitSurface(pSurface, &dest, pScreen, &offset) < 0 )
		throw ErrorInfo(SDL_GetError());
}

//***

void BaseSurface::blit(const BaseSurface& dst_surface) const
{
	const int SRC_W = pSurface->w;
	const int SRC_H = pSurface->h;
	const int DST_W = dst_surface.point()->w;
	const int DST_H = dst_surface.point()->h;

	SDL_Rect offset;
	offset.x = ( DST_W - SRC_W ) / 2;
	offset.y = ( DST_H - SRC_H ) / 2;

	if ( &dst_surface == this )
		throw ErrorInfo("Cannot blit surface to itself!");

	if ( SDL_BlitSurface(pSurface, 0, dst_surface.point(), &offset) < 0 )
		throw ErrorInfo(SDL_GetError());
}

void BaseSurface::blit(const BaseSurface& dst_surface, int any_num) const
{
	if ( &dst_surface == this )
		throw ErrorInfo("Cannot blit surface to itself!");

	if ( SDL_BlitSurface(pSurface, 0, dst_surface.point(), 0) < 0 )
		throw ErrorInfo(SDL_GetError());
}

void BaseSurface::blit(const BaseSurface& dst_surface, int at_x, int at_y) const
{
	SDL_Rect offset;
	offset.x = at_x;
	offset.y = at_y;

	if ( &dst_surface == this )
		throw ErrorInfo("Cannot blit surface to itself!");

	if ( SDL_BlitSurface(pSurface, 0, dst_surface.point(), &offset) < 0 )
		throw ErrorInfo(SDL_GetError());
}

void BaseSurface::blit(const BaseSurface& dst_surface,
	int at_x, int at_y,
	int from_x, int from_y, int w, int h,
	int delta_x, int delta_y) const
{
	SDL_Rect offset;
	offset.x = at_x - delta_x;
	offset.y = at_y - delta_y;

	SDL_Rect dest;
	dest.x = from_x - delta_x;
	dest.y = from_y - delta_y;
	dest.w = w + delta_x*2;
	dest.h = h + delta_y*2;

	if ( &dst_surface == this )
		throw ErrorInfo("Cannot blit surface to itself!");

	if ( SDL_BlitSurface(pSurface, &dest, dst_surface.point(), &offset) < 0 )
		throw ErrorInfo(SDL_GetError());
}

//***

void BaseSurface::colorKey(Uint8 r, Uint8 g, Uint8 b, Uint32 flag)
{
	Uint32 colorkey = SDL_MapRGB(pSurface->format, r, g, b);
	if ( SDL_SetColorKey(pSurface, flag, colorkey ) < 0 )
		throw ErrorInfo(SDL_GetError());
}

//************************************


//************************************
//class PictureSurface

PictureSurface::PictureSurface():BaseSurface(),fileName(NULL){};

PictureSurface::PictureSurface(const std::string& file_name, const ScreenSurface& screen):
BaseSurface(),
	fileName(file_name)
{
	SDL_Surface* pSurfaceTemp = IMG_Load(fileName.c_str());
	if ( pSurfaceTemp == 0 )
		throw ErrorInfo(IMG_GetError());
	pSurface = SDL_DisplayFormat(pSurfaceTemp);
	if ( pSurface == 0 )
		throw ErrorInfo(SDL_GetError());
	SDL_FreeSurface(pSurfaceTemp);

	pScreen = screen.point();
}

//************************************



//************************************
//class TextSurface

int TextSurface::textNum = 0;

TextSurface::TextSurface():BaseSurface(),pFont(0),message(NULL),TTF_fileName(NULL),TTF_size(28),r(0xFF),g(0xFF),b(0xFF){}
TextSurface::TextSurface(const std::string& _message, const ScreenSurface& screen,
	Uint8 _r, Uint8 _g, Uint8 _b, 
	int ttf_size, const std::string& ttf_fileName):
BaseSurface(),
	message(_message), TTF_fileName(ttf_fileName), TTF_size(ttf_size), 
	r(_r), g(_g), b(_b)
{
	if ( textNum == 0 )
	{
		if ( TTF_Init() < 0 )
		{
			throw ErrorInfo(TTF_GetError());
		}
	}

	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Blended(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);

	pScreen = screen.point();

	textNum++;
}


TextSurface::TextSurface(const TextSurface& copy):
BaseSurface(copy),
	message(copy.message), TTF_fileName(copy.TTF_fileName), TTF_size(copy.TTF_size), 
	r(copy.r), g(copy.g), b(copy.b)
{
	textNum++;
}


TextSurface::~TextSurface()
{
	textNum--;
	if ( textNum == 0 )
	{
		TTF_Quit();
	}
}

//***

void TextSurface::toBlended()
{
	SDL_FreeSurface(pSurface);

	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Blended(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}

void TextSurface::toSolid()
{
	SDL_FreeSurface(pSurface);

	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Solid(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}

void TextSurface::toShaded(Uint8 _r, Uint8 _g, Uint8 _b)
{
	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	SDL_Color bgColor;
	bgColor.r = _r;
	bgColor.g = _g;
	bgColor.b = _b;

	SDL_FreeSurface(pSurface);

	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Shaded(pFont, message, textColor, bgColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}

void TextSurface::setMessage(const std::string& _message)
{
	SDL_FreeSurface(pSurface);

	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
	message = _message;

	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Blended(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}

void TextSurface::setColor(Uint8 _r, Uint8 _g, Uint8 _b)
{
	SDL_FreeSurface(pSurface);

	SDL_Color textColor;
	textColor.r = r = _r;
	textColor.g = g = _g;
	textColor.b = b = _b;

	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Blended(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}

void TextSurface::setSize(int ttf_size)
{
	SDL_FreeSurface(pSurface);

	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	TTF_size = ttf_size;
	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());
	pSurface = myTTF_RenderString_Blended(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}

void TextSurface::setFont(const std::string& ttf_fileName)
{
	SDL_FreeSurface(pSurface);

	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	TTF_fileName = ttf_fileName;
	TTF_Font* pFont = TTF_OpenFont(TTF_fileName.c_str(), TTF_size);
	if ( pFont == 0 )
		throw ErrorInfo(TTF_GetError());

	pSurface = myTTF_RenderString_Blended(pFont, message, textColor);
	if ( pSurface == 0 )
		throw ErrorInfo(TTF_GetError());
	TTF_CloseFont(pFont);
}
