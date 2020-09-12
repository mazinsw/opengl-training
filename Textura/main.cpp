#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <gl/gl.h>
#include <gl/glu.h>
#include <SOIL.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Point3f;

const GLfloat vertexes[8][3] =
{
	{ -1.0f, -1.0f,  1.0f},
	{  1.0f, -1.0f,  1.0f},
	{  1.0f,  1.0f,  1.0f},
	{ -1.0f,  1.0f,  1.0f},
	{ -1.0f, -1.0f, -1.0f},
	{  1.0f, -1.0f, -1.0f},
	{  1.0f,  1.0f, -1.0f},
	{ -1.0f,  1.0f, -1.0f}
};

class GLWindow: public GLWindowBase
{
private:
	char str[50];
	GLfloat ry;
	GLuint textureId;
protected:
	void onResize(int width, int height)
	{
		resize3DScene();
	}

	void onCreate()
	{
		textureId = SOIL_load_OGL_texture(
						"Textura\\crate.tga",
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_POWER_OF_TWO
						//| SOIL_FLAG_MIPMAPS
						| SOIL_FLAG_DDS_LOAD_DIRECT
					);
		if(textureId == 0)
		{
			printf("Erro: Textura não carregada!\n");
			exit(-1);
		}
		ry = 0.0f;
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		glEnable(GL_TEXTURE_2D);
	}

	void render()
	{
		// OpenGL animation code goes here
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);

		glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(ry, 0.0f, 1.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glBegin(GL_QUADS);

		// Front face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[0]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[1]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[2]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[3]);

		// Back face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[5]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[6]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[7]);

		// Top face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[5]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[1]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[0]);

		// Bottom face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[3]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[6]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[7]);

		// Right face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[1]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[5]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[6]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[2]);

		// Left face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[0]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[3]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[7]);

		glEnd();
		glPopMatrix();

		swapBuffers();
		ry += 0.4f;
		sprintf(str, "FPS: %.2f", getFPS());
		setTitle(str);
	}
};

int main(int argc, char *argv[])
{
	GLWindow mw;

	return mw.start(argc, argv);
}

