#include "texture.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL.h>
#include <stdio.h>
#include <stdlib.h>

Texture::Texture()
{
	tex_id = 0;
}

void Texture::load(std::string file, bool mipmap)
{
	unsigned char * data;
	int width, height, channels;
	GLenum format;
	
	data = SOIL_load_image(file.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
	// invert Y
	int i, j;
	for( j = 0; j * 2 < height; ++j )
	{
		int index1 = j * width * channels;
		int index2 = (height - 1 - j) * width * channels;
		for( i = width * channels; i > 0; --i )
		{
			unsigned char temp = data[index1];
			data[index1] = data[index2];
			data[index2] = temp;
			++index1;
			++index2;
		}
	}
	switch( channels )
	{
	case 1:
		format = GL_LUMINANCE;
		break;
	case 2:
		format = GL_LUMINANCE_ALPHA;
		break;
	case 3:
		format = GL_RGB;
		break;
	default:
		format = GL_RGBA;
	}
	if(data == NULL)
	{
		fprintf(stderr, "%s\n", SOIL_last_result());
		exit(-2);
	}
	//IMAGE* img = ImageLoad(file.c_str());
	glGenTextures(1, &tex_id);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(mipmap)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, channels, width, height, format,
						  GL_UNSIGNED_BYTE, (GLvoid*)data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, format,
					 GL_UNSIGNED_BYTE, (GLvoid*)data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	SOIL_free_image_data(data);
	//ImageFree(img);
}
