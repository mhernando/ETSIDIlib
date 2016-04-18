

#include "TextureCache.h"
#include "Errors.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <vector>
int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, std::size_t in_size, bool convert_to_rgba32 = true);

namespace ETSIDI{ 

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}


GLTexture TextureCache::getTexture(std::string texturePath) {

    //lookup the texture and see if its in the map
	std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
    
    //check if its not in the map
    if (mit == _textureMap.end()) {
        //Load the texture
        GLTexture newTexture = loadPNG(texturePath);
        
        //Insert it into the map
		if(newTexture.id>0)
        _textureMap.insert(make_pair(texturePath, newTexture));

        return newTexture;
    }
    
    return mit->second;
}
GLTexture TextureCache::loadPNG(std::string filePath) {
    //Create a GLTexture and initialize all its fields to 0
    GLTexture texture = {};
    
    //This is the input data to decodePNG, which we load from a file
    std::vector<unsigned char> in;
    //This is the output data from decodePNG, which is the pixel data for our texture
    std::vector<unsigned char> out;

    unsigned long width, height;

    //Read in the image file contents into a buffer
    if (readFileToBuffer(filePath, in) == false) {
        fatalError("Failed to load PNG file to buffer!: "+filePath);
    }

    //Decode the .png format into an array of pixels
    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
    if (errorCode != 0) {
        fatalError("decodePNG failed " );
    }
	glEnable(GL_TEXTURE_2D);

    //Generate the openGL texture object
    glGenTextures(1, &(texture.id));

    //Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture.id);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps( GL_TEXTURE_2D, 4,
						width, height,GL_RGBA, GL_UNSIGNED_BYTE,
						&(out[0]) );

    //Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    //Return a copy of the texture data
    return texture;
}


bool TextureCache::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }

    //seek to the end
    file.seekg(0, std::ios::end);

    //Get the file size
    int fileSize = (int)(file.tellg());
    file.seekg(0, std::ios::beg);

    //Reduce the file size by any header bytes that might be present
    fileSize -= (int)(file.tellg());

    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize);
    file.close();

    return true;
}
}