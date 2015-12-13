#include"SurfaceClass.h"
#include <string>
class AmnArg
{
protected:
	const int initX;
	const int initY;
	int kind;
    int beginX;
    int beginY;
    int endX;
    int endY;
	int lastX;
	int lastY;
	std::string bg_FileName;
	std::string s_FileName;
    const ScreenSurface& screen;
	SDL_Thread * Amn;
    //
    static int amn_v(void* pThat);
	static int amn_g(void* pThat);
	static int amn_control(void* pThat);
	SDL_Thread* createThrd();
public:
    AmnArg(int _kind, int begin_x, int begin_y, int end_x, int end_y,const std::string& bg_filename, const std::string& s_filename, const ScreenSurface& _screen);
	void start();
	void stop();
	void goon();
    void show() const;
    void set(int x ,int y );
	void reset();
	int getX() const;
	int getY() const;
};

class Strip:public AmnArg
{
protected:
	const int init_l;
	int length;
	int last_l;
	std::string sbg_FileName;
	static int amn_loading(void* pThat);
	static int amn_time(void* pThat);
public:
	Strip(int begin_x, int begin_y, int end_x, int end_y, int l, const std::string& bg_filename, const std::string& s_filename,const std::string& sbg_filename, const ScreenSurface& _screen);
	SDL_Thread* createThrd_loading();
	SDL_Thread* createThrd_time();
	void show() const;
	void set(int l);
	void reset();
	int getLength() const;
};