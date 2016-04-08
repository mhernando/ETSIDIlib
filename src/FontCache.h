#pragma once
#include <map>
#include <string>
#include <Windows.h>
#include "oglft/oglft.h"

typedef  OGLFT::Monochrome fontType;
//This caches the textures so that multiple sprites can use the same textures
class FontCache
{
public:
    FontCache();
    ~FontCache();
	fontType *getFont(std::string fontPath, int size);
    

private:
    std::map<std::string, fontType *> _fontMap;
};

