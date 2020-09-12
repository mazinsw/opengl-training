#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <gl/gl.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"

typedef struct
{
	GLfloat x;
	GLfloat y;
} Point2f;

class ScreenPoint
{
private:
	GLfloat ax, ay;
public:
	int direction;
	Point2f point;

	ScreenPoint(int width, int height)
	{
		ax = Random::range(0.5f, 1.0f) * ((float)width / height) * 0.01f;
		ay = Random::range(0.5f, 1.0f) * ((float)height / width) * 0.01f;
		point.x = Random::range(-1.0f, 1.0f);
		point.y = Random::range(-1.0f, 1.0f);
		direction = Random::range(0, 3);
	}

	void render()
	{
		glVertex2f(point.x, point.y);
		switch(direction)
		{
		case 1://top right
			point.x += ax;
			point.y -= ay;
			if(point.x >= 1.0f)
			{
				point.x = 1.0f;
				direction = 2;
			}
			else if(point.y <= -1.0f)
			{
				point.y = -1.0f;
				direction = 0;
			}
			break;
		case 2://up left
			point.x -= ax;
			point.y -= ay;
			if(point.y <= -1.0f)
			{
				point.y = -1.0f;
				direction = 3;
			}
			else if(point.x <= -1.0f)
			{
				point.x = -1.0f;
				direction = 1;
			}
			break;
		case 3://bottom left
			point.x -= ax;
			point.y += ay;
			if(point.x <= -1.0f)
			{
				point.x = -1.0f;
				direction = 0;
			}
			else if(point.y >= 1.0f)
			{
				point.y = 1.0f;
				direction = 2;
			}
			break;
		default:// bottom right
			point.x += ax;
			point.y += ay;
			if(point.y >= 1.0f)
			{
				point.y = 1.0f;
				direction = 1;
			}
			else if(point.x >= 1.0f)
			{
				point.x = 1.0f;
				direction = 3;
			}
		}
	}
};

class GLWindow: public GLWindowBase
{
private:
	ScreenPoint * points[4];
	char str[50];
protected:
	void onCreate()
	{
		Random::sort();
		unsigned int i;

		for(i = 0; i < 4; i++)
			points[i] = new ScreenPoint(getWidth(), getHeight());
	}

	void onDestroy()
	{
		unsigned int i;

		for(i = 0; i < 4; i++)
			delete points[i];
	}
	void render()
	{
		// OpenGL animation code goes here

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		glPushMatrix();

		unsigned int i;

		glBegin(GL_LINE_LOOP);

		glColor3f(0.5f, 1.0f, 0.5f);
		for(i = 0; i < 4; i++)
			points[i]->render();
		glEnd();
		glPopMatrix();

		swapBuffers();

		sprintf(str, "FPS: %.2f", getFPS());
		setTitle(str);
	}
};

int main(int argc, char *argv[])
{
	GLWindow mw;

	return mw.start(argc, argv);
}

