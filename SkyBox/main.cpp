#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <SOIL.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"

#define BOX_SIZE 1.0f

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Point3f;

const GLfloat vertexes[8][3] =
{
	{ -BOX_SIZE, -BOX_SIZE,  BOX_SIZE},
	{  BOX_SIZE, -BOX_SIZE,  BOX_SIZE},
	{  BOX_SIZE,  BOX_SIZE,  BOX_SIZE},
	{ -BOX_SIZE,  BOX_SIZE,  BOX_SIZE},
	{ -BOX_SIZE, -BOX_SIZE, -BOX_SIZE},
	{  BOX_SIZE, -BOX_SIZE, -BOX_SIZE},
	{  BOX_SIZE,  BOX_SIZE, -BOX_SIZE},
	{ -BOX_SIZE,  BOX_SIZE, -BOX_SIZE}
};

class GLWindow: public GLWindowBase
{
private:
	const char * skyBoxes[6];
	char str[50];
	GLfloat rot_y, rot_x, rot_z;
	GLuint skyBoxId[6];
	int old_x, old_y;
protected:
	void onResize(int width, int height)
	{
		resize3DScene();
	}

	void onCreate()
	{
		int i;

		old_x = getWidth() / 2;
		old_y = getHeight() / 2;
		setMousePos(old_x, old_y);
		showMouse(false);
		lockMouse(true);

		skyBoxes[0] = "SkyBox\\front.png";
		skyBoxes[1] = "SkyBox\\back.png";
		skyBoxes[2] = "SkyBox\\top.png";
		skyBoxes[3] = "SkyBox\\bottom.png";
		skyBoxes[4] = "SkyBox\\right.png";
		skyBoxes[5] = "SkyBox\\left.png";

		for(i = 0; i < 6; i++)
		{
			skyBoxId[i] = SOIL_load_OGL_texture(
							  skyBoxes[i],
							  SOIL_LOAD_AUTO,
							  SOIL_CREATE_NEW_ID,
							  SOIL_FLAG_POWER_OF_TWO
							  | SOIL_FLAG_MIPMAPS
							  | SOIL_FLAG_DDS_LOAD_DIRECT
						  );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)

			if(skyBoxId[i] == 0)
			{
				printf("Textura '%s' não carregada!", skyBoxes[i]);
				exit(-1);
			}
		}
		rot_x = rot_y = rot_z = 0.0f;
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		glEnable(GL_TEXTURE_2D);
	}

	void onMouseMove(int x, int y)
	{
		rot_y += (GLfloat)(x - old_x) / getWidth() * 180.0f;
		rot_x += (GLfloat)(y - old_y) / getWidth() * 180.0f;

		if(rot_y > 360.0f)
			rot_y -= 360.0f;
		else if(rot_y < 0.0f)
			rot_y += 360.0f;
		if(x <= getWidth() / 3 || x >= getWidth() * (2.0f / 3))
		{
			old_x = getWidth() / 2;
			setMousePos(old_x, y);
		}
		else
			old_x = x;
		if(rot_x > 360.0f)
			rot_x -= 360.0f;
		else if(rot_x < 0.0f)
			rot_x += 360.0f;
		if(y <= getHeight() / 3 || y >= getHeight() * (2.0f / 3))
		{
			old_y = getHeight() / 2;
			setMousePos(x, old_y);
		}
		else
			old_y = y;
	}

	void render()
	{
		// OpenGL animation code goes here
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glPushMatrix();

		glRotatef(rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef(rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef(rot_z, 0.0f, 0.0f, 1.0f);

		glDisable(GL_DEPTH_TEST);// Disables Depth Testing

		glScalef(25.0f, 25.0f, 25.0f);
		// Front face
		glBindTexture(GL_TEXTURE_2D, skyBoxId[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[0]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[1]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[2]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[3]);
		glEnd();

		// Back face
		glBindTexture(GL_TEXTURE_2D, skyBoxId[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[5]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[6]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[7]);
		glEnd();

		// Top face
		glBindTexture(GL_TEXTURE_2D, skyBoxId[3]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[5]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[1]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[0]);
		glEnd();

		// Bottom face
		glBindTexture(GL_TEXTURE_2D, skyBoxId[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[3]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[6]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[7]);
		glEnd();

		// Right face
		glBindTexture(GL_TEXTURE_2D, skyBoxId[4]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[1]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[5]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[6]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[2]);
		glEnd();

		// Left face
		glBindTexture(GL_TEXTURE_2D, skyBoxId[5]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vertexes[4]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vertexes[0]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(vertexes[3]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertexes[7]);
		glEnd();

		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

		glPopMatrix();
		swapBuffers();

		sprintf(str, "rot_x: %.2f°  -  rot_y: %.2f° @ %.2f FPS", rot_x, rot_y, getFPS());
		//sprintf(str, "X: %d   -   Y: %d", x, y);
		setTitle(str);
	}
};

int main(int argc, char *argv[])
{
	GLWindow mw;

	return mw.start(argc, argv);
}

