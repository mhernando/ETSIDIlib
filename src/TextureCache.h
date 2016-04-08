#pragma once

#include <string>
#include <map>
#include <vector>
//This caches the textures so that multiple sprites can use the same textures
using namespace std;


#include "ETSIDI.h"

namespace ETSIDI{

class TextureCache
{
public:
    TextureCache();
    ~TextureCache();

    GLTexture getTexture(string texturePath);

private:
    map<string, GLTexture> _textureMap;
	bool readFileToBuffer(string filePath, vector<unsigned char>& buffer);
	GLTexture loadPNG(string filePath);
};

}