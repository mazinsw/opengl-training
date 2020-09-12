#include "model.h"
#include <stdio.h>

Model::Model(TextureManager* texman)
{
	this->texman = texman;
}

void Model::render()
{
	render_object(shapes, texman);
}

float* Model::getVertexes()
{
	return &shapes[0].mesh.positions[0];
}

unsigned int Model::getVertexCount()
{
	return shapes[0].mesh.positions.size() / 3;
}

void Model::load(std::string model)
{
	std::string mtl_base;
	std::string::size_type pos;
	
	pos = model.rfind('/');
	if(pos != std::string::npos)
		mtl_base.append(model, 0, pos + 1);
	load_object(model, mtl_base, shapes, texman);
	refresh();
}