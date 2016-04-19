#include "EasyPlayer.h"


//singleton for the audio system
FMOD_SYSTEM  *EasyPlayer::system=0;
unsigned int EasyPlayer::version=0;


void EasyPlayer::initialize()
{

	void *extradriverdata = 0;
	if(system==0){
		result=FMOD_System_Create(&system);
		//result = system->getVersion(&version);
		result = FMOD_System_Init(system, 48, FMOD_INIT_NORMAL, extradriverdata);
	}
	
}
#include <iostream>
FMOD_SOUND *EasyPlayer::getSound(std::string soundPath)
{
	FMOD_SOUND *newSound=0;
	std::map<std::string, FMOD_SOUND *>::iterator mit = _soundMap.find(soundPath);
    initialize();
    //check if its not in the map
    if (mit == _soundMap.end()) {
        //Load the sound	
		result = FMOD_System_CreateSound(system, soundPath.c_str(), FMOD_DEFAULT, 0, &newSound);
        _soundMap.insert(make_pair(soundPath, newSound));
    }
	else newSound=mit->second;
	return newSound;
}

FMOD_CHANNEL *EasyPlayer::playSound(std::string soundPath)
{
	static int counter=0;
	FMOD_SOUND *newSound=getSound(soundPath);
	FMOD_CHANNEL    *channel = 0;
	FMOD_System_Update(system);
  	FMOD_System_PlaySound(system,newSound, 0, false, &channel);

	return channel;
}

void EasyPlayer::playMusic(std::string soundPath, bool loop)
{
	FMOD_SOUND *newSound=getSound(soundPath);
	if(music_channel!=0){//there is music
		FMOD_Channel_Stop(music_channel);
	}
	music=newSound;
	result = FMOD_System_PlaySound(system,newSound, 0, false, &music_channel);
	if(loop)FMOD_Channel_SetMode(music_channel, FMOD_2D|FMOD_LOOP_NORMAL);
	else FMOD_Channel_SetMode(music_channel, FMOD_2D|FMOD_LOOP_OFF);
}
 
void EasyPlayer::stopMusic()
{
	if(music_channel!=0){//there is music
		FMOD_Channel_Stop(music_channel);
	}
}
EasyPlayer::~EasyPlayer()
{
	//habra que recorrer todo y pararlo
}