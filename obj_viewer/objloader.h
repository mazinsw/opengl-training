#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_
#include "texturemanager.h"
#include "tiny_obj_loader.h"

void load_object(std::string file, std::string mtl_base, 
	std::vector<tinyobj::shape_t>& shapes, TextureManager* texman);
void render_object(const std::vector<tinyobj::shape_t>& shapes, 
	TextureManager* texman);

#endif /* _OBJLOADER_H_ */