#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_
#include <map>
#include "texture.h"

class TextureManager
{
private:
	std::map<std::string, Texture*> textures;
public:
	~TextureManager();
	void load(std::string filename, std::string name, bool mipmap = false);
	unsigned int getId(std::string name);
};

#endif /* _TEXTUREMANAGER_H_ */