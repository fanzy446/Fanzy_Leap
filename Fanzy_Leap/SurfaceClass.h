#ifndef SURFACE_CLASS_HPP
#define SURFACE_CLASS_HPP

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL_render_Chinese.h"

class ScreenSurface
{
private:
	//number of screen, make sure there is only ONE screen
	static int screenNum;
	//size & bpp  of screen
	int width;
	int height;
	int bpp;
	//common flags:SDL_SWSURFACE, SDL_HWSURFACE, SDL_DOUBLEBUF, SDL_FULLSCREEN
	Uint32 flags;
	//other attribute
	SDL_Surface* pScreen;
	std::string windowName;
	std::string iconName;

public:
	//construct & deconstruct
	ScreenSurface();
	ScreenSurface(int w, int h, const std::string& window_name = "NULL", const std::string& icon_name = "NULL", int b = 0, Uint32 f = 0);
	~ScreenSurface();
	//screen's point
	SDL_Surface* point() const;
	//flip the screen
	void flip() const;
	//fill the screen with some color, default is black.
	void fillColor(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0) const;
};

class BaseSurface
{
private:
	//
protected:
	SDL_Surface* pScreen;
	SDL_Surface* pSurface;
public:
	BaseSurface();
	BaseSurface(const BaseSurface& copy);
	virtual ~BaseSurface();
	BaseSurface& operator=(const BaseSurface& copy);
	//surface's point
	SDL_Surface* point() const;
	//blit surface to screen
	void blit() const;
	void blit(int any_num) const;
	void blit(int at_x, int at_y) const;
	void blit(int at_x, int at_y,
		int from_x, int from_y, int w, int h,
		int delta_x = 0, int delta_y = 0) const;
	//blit surface to another surface
	void blit(const BaseSurface& dst_surface) const;
	void blit(const BaseSurface& dst_surface, int any_num) const;
	void blit(const BaseSurface& dst_surface,
		int at_x, int at_y) const;
	void blit(const BaseSurface& dst_surface,
		int at_x, int at_y,
		int from_x, int from_y, int w, int h,
		int delta_x = 0, int delta_y = 0) const;
	//color keying
	void colorKey(Uint8 r = 0, Uint8 g = 0xFF, Uint8 b = 0xFF, Uint32 flag = SDL_SRCCOLORKEY);
};

class PictureSurface:public BaseSurface
{
private:
	std::string fileName;
public:
	PictureSurface();
	PictureSurface(const std::string& file_name, const ScreenSurface& screen);
};

class TextSurface:public BaseSurface
{
private:
	static int textNum;
	TTF_Font* pFont;
	std::string message;
	std::string TTF_fileName;
	int TTF_size;
	Uint8 r, g, b;
public:
	TextSurface();
	TextSurface(const std::string& _message, const ScreenSurface& screen,
		Uint8 _r = 0xFF, Uint8 _g = 0xFF, Uint8 _b = 0xFF, 
		int ttf_size = 25, const std::string& ttf_fileName = "./fonts/STXINWEI.TTF");
	TextSurface(const TextSurface& copy);
	~TextSurface();
	//text tools
	void toBlended();
	void toSolid();
	void toShaded(Uint8 _r, Uint8 _g, Uint8 _b);
	void setMessage(const std::string& _message);
	void setColor(Uint8 _r, Uint8 _g, Uint8 _b);
	void setSize(int ttf_size);
	void setFont(const std::string& ttf_fileName);
};

class ErrorInfo
{
private:
	std::string info;
public:
	ErrorInfo():info("Unknown ERROR!")
	{}
	ErrorInfo(const char* c_str)
	{
		info = std::string(c_str);
	}
	ErrorInfo(const std::string& str):info(str)
	{}
	void show() const
	{
		std::cerr << info << std::endl;
	}
};

#endif