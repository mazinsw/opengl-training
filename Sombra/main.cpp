#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../classes/shader.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"

const GLchar *vertex_shader[] =
{
	"void main(void) {\n",
	"    gl_Position = ftransform();\n",
	"    gl_FrontColor = gl_Color;\n",
	"}"
};

const GLchar *color_shader[] =
{
	"void main() {\n",
	"    gl_FragColor = gl_Color;\n",
	"}"
};

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
	GLfloat rx, ry, rz;

public:
	void onResize(int width, int height)
	{
		resize3DScene();
	}

	void onCreate()
	{
		rx = ry = rz = 0.0f;
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	}

	void onMouseMove(int x, int y)
	{
		sprintf(str, "X: %d, Y: %d; FPS: %.2f", x, y, getFPS());
		setTitle(str);
	}

	void render()
	{
		// OpenGL animation code goes here
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);

		glRotatef(rx, 1.0f, 0.0f, 0.0f);
		glRotatef(ry, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		
		// compile and link the specified shaders:
		static shader_prog prog(vertex_shader, color_shader);

		// Use the compiled shaders:
		prog();

		glBegin(GL_QUADS);

		// Front face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(vertexes[0]);
		glVertex3fv(vertexes[1]);
		glVertex3fv(vertexes[2]);
		glVertex3fv(vertexes[3]);

		// Back face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glVertex3fv(vertexes[5]);
		glVertex3fv(vertexes[6]);
		glVertex3fv(vertexes[7]);

		// Top face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glVertex3fv(vertexes[5]);
		glVertex3fv(vertexes[1]);
		glVertex3fv(vertexes[0]);

		// Bottom face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3fv(vertexes[3]);
		glVertex3fv(vertexes[2]);
		glVertex3fv(vertexes[6]);
		glVertex3fv(vertexes[7]);

		// Right face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(vertexes[1]);
		glVertex3fv(vertexes[5]);
		glVertex3fv(vertexes[6]);
		glVertex3fv(vertexes[2]);

		// Left face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glVertex3fv(vertexes[0]);
		glVertex3fv(vertexes[3]);
		glVertex3fv(vertexes[7]);

		glEnd();
		glPopMatrix();

		swapBuffers();
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

