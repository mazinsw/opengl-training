#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <gl/gl.h>
#include <gl/glu.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"
#include "../classes/object.h"
#include "../classes/display.h"

class GLWindow: public GLWindowBase
{
private:
	char str[50];
	GLfloat rx, ry, rz;
	Object sphere;
protected:
	void onResize(int width, int height)
	{
		resize3DScene();
	}

	void getWindowInfo(int & width, int & height, int & bpp,
					   bool & fullscreen)
	{
		// ajusta a janela em 80% da tela do monitor
		width = Display::getWidth() * 0.8;
		height = Display::getHeight() * 0.8;
	}

	void onCreate()
	{
		// Create light components
		GLfloat sKa[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat sKd[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		GLfloat sKs[] = { 0.5f, 0.5f, 0.5f, 1.0f };

		rx = ry = rz = 0.0f;
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		if(!sphere.load("Object/sphere.obj"))
			close();
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sKd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sKs);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sKa);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glMateriali(GL_FRONT, GL_SHININESS, 25);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sKd);
	}

	void render()
	{
		GLfloat position[] = { -1.0f, 1.0f, -2.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		// OpenGL animation code goes here
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glPushMatrix();

		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(rx, 1.0f, 0.0f, 0.0f);
		glRotatef(ry, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);

		glColor3f(0.5f, 0.0f, 0.0f);
		sphere.render();
		glColor3f(0.0f, 0.5f, 0.0f);
		glTranslatef(-2.0f, 0.0f, 0.0f);
		sphere.render();
		glColor3f(0.0f, 0.0f, 0.5f);
		glTranslatef(4.0f, 0.0f, 0.0f);
		sphere.render();

		glPopMatrix();
		
		swapBuffers();
		sprintf(str, "Iluminacao - FPS: %.2f", getFPS());
		setTitle(str);
		// update rotation
		rx += 0.5f;
		ry += 0.4f;
		rz += 0.3f;
	}
};

int main(int argc, char *argv[])
{
	GLWindow mw;

	return mw.start(argc, argv);
}

