#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <math.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"
#include "../classes/object.h"

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
	GLfloat angle;
	Object monkey;
	Object sphere;
	bool renderMonkey;
protected:
	void onResize(int width, int height)
	{
		resize3DScene();
	}

	bool onInit(int argc, char** argv)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		return GLWindowBase::onInit(argc, argv);
	}

	void onCreate()
	{
		angle = 0.0f;
		glEnable( GL_MULTISAMPLE );
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		if(!monkey.load("Object/monkey.obj"))
			close();
		if(!sphere.load("Object/sphere.obj"))
			close();
		// Enable light and set up 2 light sources (GL_LIGHT0 and GL_LIGHT1)
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat col[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
		renderMonkey = true;
	}

	void onKeyDown(int key, int state)
	{
		if(key == SDLK_m)
			renderMonkey = true;
		else if(key == SDLK_s)
			renderMonkey = false;
		GLWindowBase::onKeyDown(key, state);
	}

	void render()
	{
		GLfloat pos[] = { -1.0f, 1.0f, -2.0f, 1.0f};

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		if(renderMonkey)
			monkey.render();
		else
			sphere.render();
		glPopMatrix();
		
		swapBuffers();
		angle += 0.5f;
		sprintf(str, "FPS: %.2f", getFPS());
		setTitle(str);
	}
};

int main(int argc, char *argv[])
{
	GLWindow mw;

	return mw.start(argc, argv);
}

