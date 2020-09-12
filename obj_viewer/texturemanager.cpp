#include "texturemanager.h"

TextureManager::~TextureManager()
{
	std::map<std::string, Texture*>::iterator it;
	for(it = textures.begin(); it != textures.end(); it++)
		delete it->second;
}

void TextureManager::load(std::string filename, std::string name, bool mipmap)
{
	Texture* tex;
	std::map<std::string, Texture*>::iterator it;
	
	it = textures.find(name);
	if(it != textures.end())
		return;
	tex = new Texture();
	tex->load(filename, mipmap);
	textures[name] = tex;
}

unsigned int TextureManager::getId(std::string name)
{
	std::map<std::string, Texture*>::iterator it;
	
	it = textures.find(name);
	if(it == textures.end())
		return 0;
	return it->second->getId();
}
