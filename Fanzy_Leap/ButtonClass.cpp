#include "ButtonClass.h"

//*************************
//class BaseButton

EffectSound BaseButton::es("./sounds/mouseover.ogg");
EffectSound BaseButton::ck("./sounds/click.ogg");

BaseButton::BaseButton():
atX(0), atY(0), w(0), h(0), offset(0),
	inBox(false), clickDown(false), clickUp(false)
{}

BaseButton::~BaseButton()
{}

void BaseButton::setup(int at_x, int at_y, int _offset)
{
	atX = at_x;
	atY = at_y;
	offset = _offset;
}

bool BaseButton::mouseOver(const SDL_Event& gameEvent) const
{
	if ( gameEvent.type == SDL_MOUSEMOTION )
	{
		int mouse_at_x = gameEvent.motion.x;
		int mouse_at_y = gameEvent.motion.y;
		if ( mouse_at_x >= atX && mouse_at_x <= atX + w &&
			mouse_at_y >= atY && mouse_at_y <= atY + h )
		{
			if ( inBox == false )
				es.play();
			return true;
		}
		else return false;
	}
	else return false;
}

bool BaseButton::mouseDown(const SDL_Event& gameEvent) const
{
	if ( gameEvent.type == SDL_MOUSEBUTTONDOWN )
		if( gameEvent.button.button == SDL_BUTTON_LEFT )
		{
			int mouse_at_x = gameEvent.button.x;
			int mouse_at_y = gameEvent.button.y;
			if ( mouse_at_x >= atX && mouse_at_x <= atX + w &&
				mouse_at_y >= atY && mouse_at_y <= atY + h )
			{
				if ( clickDown == false )
					ck.play();
				return true;
			}
			else return false;
		}
		else return false;
	else return false;
}

bool BaseButton::mouseUp(const SDL_Event& gameEvent) const
{
	if ( gameEvent.type == SDL_MOUSEBUTTONUP )
		if( gameEvent.button.button == SDL_BUTTON_LEFT )
		{
			int mouse_at_x = gameEvent.button.x;
			int mouse_at_y = gameEvent.button.y;
			if ( mouse_at_x >= atX && mouse_at_x <= atX + w &&
				mouse_at_y >= atY && mouse_at_y <= atY + h )
				return true;
			else return false;
		}
		else return false;
	else return false;
}

bool BaseButton::mouseUpOutside(const SDL_Event& gameEvent) const
{
	if ( gameEvent.type == SDL_MOUSEBUTTONUP )
		if( gameEvent.button.button == SDL_BUTTON_LEFT )
		{
			int mouse_at_x = gameEvent.button.x;
			int mouse_at_y = gameEvent.button.y;
			if ( mouse_at_x <= atX || mouse_at_x >= atX + w ||
				mouse_at_y <= atY || mouse_at_y >= atY + h )
				return true;
			else return false;
		}
		else return false;
	else return false;
}

bool BaseButton::effectiveClick(const SDL_Event& game_event)
{
	inBox = this->mouseOver(game_event);
	if ( this->mouseDown(game_event) == true )
	{
		clickDown = true;
		inBox = true;
	}
	if ( this->mouseUp(game_event) == true )
	{
		if ( clickDown == true )
			clickUp = true;
		inBox = true;
	}
	if ( this->mouseUpOutside(game_event) == true )
		clickDown = false;

	if ( inBox == true && clickDown == false )
	{
		this->blitOver();
		return false;
	}
	else if ( inBox == true && clickDown == true )
	{
		if ( clickUp == true )
		{
			clickUp = false;
			clickDown = false;
			this->blitOver();
			return true;
		} 
		else 
		{
			this->blitDown();
			return false;
		}
	}
	else 
	{
		this->blitOut();
		return false;
	}
}

//*************************


//*************************
//class Button

Button::Button():BaseButton(),outImg(),overImg(){};

Button::Button(const std::string& outImg_fileName, const std::string& overImg_fileName, const ScreenSurface& screen):
BaseButton(),
	outImg(PictureSurface(outImg_fileName, screen)),
	overImg(PictureSurface(overImg_fileName, screen))
{
	w = outImg.point()->w;
	h = outImg.point()->h;
}

Button::Button(const BaseSurface& out_img, const BaseSurface& over_img):
BaseButton(),
	outImg(out_img), overImg(over_img)
{
	w = outImg.point()->w;
	h = outImg.point()->h;
}

Button::Button(const std::string buttonText, const ScreenSurface& screen,
	Uint8 out_r, Uint8 out_g, Uint8 out_b, Uint8 on_r, Uint8 on_g, Uint8 on_b,
	int ttf_size, const std::string& ttf_fileName):
BaseButton(),
	outImg(TextSurface(buttonText, screen, out_r, out_g, out_b, ttf_size, ttf_fileName)),
	overImg(TextSurface(buttonText, screen, on_r, on_g, on_b, ttf_size, ttf_fileName))
{
	w = outImg.point()->w;
	h = outImg.point()->h;
}

Button::~Button()
{}

void Button::colorKey(Uint8 r, Uint8 g, Uint8 b)
{
	outImg.colorKey(r, g, b);
	overImg.colorKey(r, g, b);
}

void Button::blitOut() const
{
	outImg.blit(atX, atY);
}

void Button::blitOver() const
{
	overImg.blit(atX, atY);
}

void Button::blitDown() const
{
	overImg.blit(atX+offset, atY+offset);
}

void Button::addText(const TextSurface& out_text, const TextSurface& over_text)
{
	out_text.blit(outImg);
	over_text.blit(overImg);
}

Button& Button::operator=(const Button& copy)
{
	outImg=copy.outImg;
	overImg=copy.overImg;
	atX=copy.atX;
	atY=copy.atY;
	offset=copy.offset;
	w=copy.w;
	h=copy.h;
	inBox=copy.inBox;
	clickDown=copy.clickDown;
	clickUp=copy.clickUp;
	return *this;
}

SDL_Surface* Button::point()
{
	return outImg.point();
}
