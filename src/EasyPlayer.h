#pragma once
#include "fmod/fmod.h"

#include <map>
#include <string>

#define MAX_SOUNDS 100

class EasyPlayer
{


	//single instance
	static FMOD_SYSTEM *system;
	static unsigned int version;
	//player attributes
	FMOD_SOUND *music;
	FMOD_CHANNEL *music_channel;

	std::map<std::string, FMOD_SOUND *> _soundMap;
	void initialize();
	FMOD_SOUND *getSound(std::string soundPath);
public:
  EasyPlayer():music(0),music_channel(0){;}
  FMOD_CHANNEL * playSound(std::string soundPath);
  void playMusic(std::string soundPath, bool loop=false);
  void stopMusic();
  ~EasyPlayer();
  	FMOD_RESULT result;

};
