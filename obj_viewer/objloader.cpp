#include "objloader.h"
#include <GL/gl.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

void load_object(std::string file, std::string mtl_base, 
	std::vector<tinyobj::shape_t>& shapes, TextureManager* texman)
{
	std::string err;
	std::list<tinyobj::material_t>::iterator it;
	err = tinyobj::LoadObj(shapes, file.c_str(), mtl_base.c_str());
	if (!err.empty())
	{
		std::cerr << err << std::endl;
		exit(-1);
	}
	for (size_t i = 0; i < shapes.size(); i++)
	{
		for(it = shapes[i].materials.begin(); it != shapes[i].materials.end(); it++)
		{
			tinyobj::material_t& mtl = *it;
			if(!mtl.ambient_texname.empty())
				texman->load(mtl_base + mtl.ambient_texname, mtl.ambient_texname, mtl.mipmap);
			if(!mtl.diffuse_texname.empty())
				texman->load(mtl_base + mtl.diffuse_texname, mtl.diffuse_texname, mtl.mipmap);
			if(!mtl.specular_texname.empty())
				texman->load(mtl_base + mtl.specular_texname, mtl.specular_texname, mtl.mipmap);
			if(!mtl.normal_texname.empty())
				texman->load(mtl_base + mtl.normal_texname, mtl.normal_texname, mtl.mipmap);
		}
	}
}

void render_object(const std::vector<tinyobj::shape_t>& shapes, 
	TextureManager* texman)
{
	unsigned int tex_id;
	std::list<tinyobj::material_t>::const_iterator it;
	for(unsigned int i = 0; i < shapes.size(); i++)
	{
		for(it = shapes[i].materials.begin(); it != shapes[i].materials.end(); it++)
		{
			const tinyobj::material_t& mtl = *it;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mtl.ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mtl.diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mtl.specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mtl.shininess * 128.0f);
			// positions
			if(shapes[i].mesh.positions.size() > 0)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, &shapes[i].mesh.positions[0]);
			}
			// normals
			if(shapes[i].mesh.normals.size() > 0)
			{
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, &shapes[i].mesh.normals[0]);
			}
			// texture
			if(shapes[i].mesh.texcoords.size() > 0)
			{
				tex_id = texman->getId(mtl.diffuse_texname);
				if(tex_id != 0)
				{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, tex_id);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glTexCoordPointer(2, GL_FLOAT, 0, &shapes[i].mesh.texcoords[0]);
				}
				else
					glDisable(GL_TEXTURE_2D);
			}
			// indexes
			glDrawElements(GL_TRIANGLES, mtl.count, GL_UNSIGNED_INT, &shapes[i].mesh.indices[0] + mtl.offset);
			if(shapes[i].mesh.texcoords.size() > 0)
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			if(shapes[i].mesh.normals.size() > 0)
				glDisableClientState(GL_NORMAL_ARRAY);
			if(shapes[i].mesh.positions.size() > 0)
				glDisableClientState(GL_VERTEX_ARRAY);
		}
	}
}
