#include "ETSIDI.h"
#include "Dice.h"
#include "TextureCache.h"
#include "FontCache.h"
#include "EasyPlayer.h"
#include <cstddef>
namespace ETSIDI
{

TextureCache *textures=0;
FontCache *fonts=0;
EasyPlayer *player=0;
JUSTIFICACION_H horizontalJustification=ORIGEN;
JUSTIFICACION_V verticalJustification=LINEA_BASE;
GLfloat textColor[4]={1.F,1.F,1.F,1.F};
double lanzaDado(double max, double min){return Dice::Double(max,min);}
int lanzaDado(int max, int min){	return Dice::Int(max,min);}
bool lanzaMoneda(){	return Dice::Bool();}

GLTexture getTexture(string texturePath)
{
	if(textures==0)textures=new TextureCache();
	return textures->getTexture(texturePath);
}

long getMillis()
{
    return GetTickCount();
}

void play(std::string soundPath)
{
	if(player==0)player=new EasyPlayer();
	player->playSound(soundPath);
}
void playMusica(std::string soundPath, bool repite)
{
	if(player==0)player=new EasyPlayer();
	player->playMusic(soundPath,repite);
}
void stopMusica()
{
	if(player==0)player=new EasyPlayer();
	player->stopMusic();
}
void print(  const char *txt, const char *fuente, int size)
{
	if(fonts==0)fonts=new FontCache();
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glDisable(GL_LIGHTING);
	fontType *font= fonts->getFont(fuente,size);
	if(!font)return;
	font->setForegroundColor(textColor);
	font->setHorizontalJustification( OGLFT::Face::HorizontalJustification(horizontalJustification) );
	font->setVerticalJustification( OGLFT::Face::VerticalJustification(verticalJustification) );
	font->draw(0,0, txt );
	glEnable(GL_LIGHTING);
}
void setTextColor(float r, float g, float b, float alpha)
{
	textColor[0]=r;
	textColor[1]=g;
	textColor[2]=b;
	textColor[3]=alpha;
}

}//namespace ETSIDI