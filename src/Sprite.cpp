#include "ETSIDI.h"

namespace ETSIDI
{



double Sprite::tick()
{
	long uptime = getMillis();
	double secs=(uptime-last_update)/1000.0;
	last_update=uptime;
	return secs;
}

Sprite::~Sprite()
{

}

bool checkPointIntoRec(Vector2D ori, Vector2D ux, Vector2D uy, Vector2D point)
{
	Vector2D dif=point-ori;
	if((dif*ux>0)&&(dif*ux<ux*ux)&&
		(dif*uy>0)&&(dif*uy<uy*uy))return true;
	return false;
}

bool Sprite::collides(const Sprite &s) const
{
	//check if the sprites rectangles superimposes
	double _ang=_angle*3.1415/180;
	Vector2D x_b(cos(_ang), sin(_ang));
	Vector2D y_b(x_b.y,-x_b.x);
	//real origin (considering the anchor offset)
	Vector2D or1=pos-x_b*anchor.x-y_b*anchor.y;
	x_b=x_b*_width;
	y_b=y_b*_height;

	//compute the other sprite vectors and origin:
	double _ang2=s._angle*3.1415/180;
	Vector2D x_b2(cos(_ang2), sin(_ang2));
	Vector2D y_b2(x_b2.y,-x_b2.x);
	//real origin (considering the anchor offset)
	Vector2D or2=s.pos-x_b2*s.anchor.x-y_b2*s.anchor.y;
	x_b2=x_b2*s._width;
	y_b2=y_b2*s._height;

	//check if any vertex of a is into b
	if(checkPointIntoRec(or1, x_b, y_b, or2))return true;
	if(checkPointIntoRec(or1, x_b, y_b, or2+x_b2))return true;
	if(checkPointIntoRec(or1, x_b, y_b, or2+y_b2))return true;
	if(checkPointIntoRec(or1, x_b, y_b, or2+y_b2+x_b2))return true;

	//check if any vertex of b is into a
	if(checkPointIntoRec(or2, x_b2, y_b2, or1))return true;
	if(checkPointIntoRec(or2, x_b2, y_b2, or1+x_b))return true;
	if(checkPointIntoRec(or2, x_b2, y_b2, or1+y_b))return true;
	if(checkPointIntoRec(or2, x_b2, y_b2, or1+y_b+x_b))return true;

	return false;

}
Sprite::Sprite(const char *texturePath, float x, float y,  float width, float height) {
	tick();
	
    //Set up our private vars
    pos=Vector2D(x,y);
	strncpy(_texturePath, texturePath,254);
	_texture=getTexture(texturePath);
    
	setSize(width,height);
	anchor=Vector2D(width,height)*0.5;
	horizontal_flip=vertical_flip=false;
	_angle=0;
 }

//Draws the sprite to the screen
void Sprite::draw() {
	
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.01);
	glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(_texture.id==0)_texture=getTexture(_texturePath);
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	glDisable(GL_LIGHTING);
	


	glColor3f(1,1,1); //de momento
	glPushMatrix();
	
	glTranslated(pos.x, pos.y,0);
	if(horizontal_flip)glScalef(-1,1,1);
	if(vertical_flip)glScalef(1,-1,1);
	glRotated(_angle,0,0,1);
	glTranslated(-anchor.x, -anchor.y,0);
	glBegin(GL_POLYGON);
	
	
	glTexCoord2d(0,1);		glVertex2f(0,0);
	glTexCoord2d(1,1);		glVertex2f(_width,0);
	glTexCoord2d(1,0);		glVertex2f(_width,_height);
	glTexCoord2d(0,0);		glVertex2f(0,_height);
	glEnd();

	glPopMatrix();
	 glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);	
	 glDisable(GL_TEXTURE_2D);
	 glDisable(GL_ALPHA_TEST);
	//update is after draw... so it is possible to correct sprites position before next drawing
}

void Sprite::loop() {
	double time=tick();
	pos=pos+vel*time;
}

} //namespace ETSIDI