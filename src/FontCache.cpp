#include "FontCache.h"

#include <sstream>
#include <string>

FontCache::FontCache()
{
	
}


FontCache::~FontCache()
{
	//TODO: recorrer y cerrar fuentes: if(font)TTF_CloseFont(font);
}


fontType *FontCache::getFont(std::string fontPath, int size){

    //lookup the texture and see if its in the map
	std::string nkey = static_cast<std::ostringstream*>( &(std::ostringstream() << size) )->str();
	std::string key = fontPath+nkey;

	std::map<std::string, fontType *>::iterator mit = _fontMap.find(key);
    
    //check if its not in the map
    if (mit == _fontMap.end()) {
        //Load the font

		fontType *newfont = new fontType(fontPath.c_str(), size);
        
        
        //Insert it into the map
		if(newfont)
        _fontMap.insert(make_pair(key, newfont));

        return newfont;
    }
    
    return mit->second;
}