#include "ETSIDI.h"

namespace ETSIDI{

SpriteSequence::~SpriteSequence()
{
	
}

//Initializes the sprite VBO. x, y, width, and height are
//in the normalized device coordinate space. so, [-1, 1]
SpriteSequence::SpriteSequence(const char *texturePath, int cols, int rows, int ms_step, bool repeat, 
							   float x, float y, float w, float h, int initState):Sprite(texturePath,x,y,w,h)
{


_cols=cols;
_rows=rows;
initial_time=last_update;
_ms_step=ms_step;
if(w<0)_width=_width/cols;
if(h<0)_height=_height/rows;
anchor=Vector2D(_width,_height)*0.5;
setState(initState,false);
_repeat=repeat;
 }
void SpriteSequence::setState(int index, bool pause)
{
	//initial_time=last_update-index*_ms_step;
	_pause=pause;
	state=index%(_rows*_cols);
}
int SpriteSequence::getState()
{
	return state;
}
//Draws the sprite to the screen
void SpriteSequence::loop()
{
	Sprite::loop();
	if(_pause)initial_time=last_update;

	//time based state update
	if(last_update-initial_time>_ms_step){
		state+=(last_update-initial_time)/_ms_step;
		initial_time=last_update+ (last_update-initial_time)%_ms_step;
	}
	if((!_repeat)&&(state>=_rows*_cols)){state=_rows*_cols-1;_pause=true;}
	else state%=(_rows*_cols);




}
void SpriteSequence::draw() {

	
	int row=state/_cols;
	int col=state%_cols;

	glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glAlphaFunc(GL_GREATER, 0.01);
	glEnable(GL_ALPHA_TEST);
	if(_texture.id==0)_texture=getTexture(_texturePath);
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1); //de momento


	glPushMatrix();
	glTranslated(pos.x, pos.y,0);
	if(horizontal_flip)glScalef(-1,1,1);
	if(vertical_flip)glScalef(1,-1,1);
	glRotated(getAngle(),0,0,1);
	glTranslated(-anchor.x, -anchor.y,0);
	
	glBegin(GL_POLYGON);
	glTexCoord2d((double)col/_cols,(double)(row+1)/_rows);		glVertex2f(0,0);
	glTexCoord2d((double)(col+1)/_cols,(double)(row+1)/_rows);		glVertex2f(_width,0);
	glTexCoord2d((double)(col+1)/_cols,(double)(row)/_rows);		glVertex2f(_width,_height);
	glTexCoord2d((double)col/_cols,(double)(row)/_rows);		glVertex2f(0,_height);
	glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);	
    glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	
}

}