#pragma once

#include "Sprite.h"

//A 2D quad that can be rendered to the screen
class SpriteSequence: public Sprite
{
public:
    SpriteSequence(GLTexture texture, int cols, int rows=1, int ms_step = 50, bool repeat = true, float x=0, float y=0, float w=-1.0F, float h=-1.0F, int initState=0);
    ~SpriteSequence();
    virtual void draw();
	void setState(int index, bool pause=true);
	int getState();
	void pause(bool stop=true){_pause=stop;}
	
protected:
	int _cols, _rows;
	long int initial_time;
	int _ms_step;
	bool _pause;
	int state;
	bool _repeat;
};

