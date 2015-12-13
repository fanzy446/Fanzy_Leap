#ifndef MIX_SOUND_CLASS_HPP
#define MIX_SOUND_CLASS_HPP

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

class BaseMixSound
{
private:
	static int MixNUM;
protected:
	BaseMixSound();
public:
	virtual ~BaseMixSound();
};

class EffectSound: public BaseMixSound
{
private:
	Mix_Chunk* sound;
public:
	EffectSound(const std::string& sound_fileName);
	~EffectSound();
	void play() const;
};

class MusicSound: public BaseMixSound
{
private:
	Mix_Music* music;
public:
	MusicSound(const std::string& music_fileName);
	~MusicSound();
	void play() const;
	void stop() const;
};

#endif