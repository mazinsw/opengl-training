#include <stdlib.h>
#include <stdio.h>
#include <gl/gl.h>
#include "../classes/glwindow.h"
#include "../classes/font.h"

class GLWindow: public GLWindowBase
{
private:
	char str[50];
	Font* font;
protected:
	bool onInit(int argc, char * argv[])
	{
		setTitle("OpenGL TrueType Fonts");
		return GLWindowBase::onInit(argc, argv);
	}

	void onCreate()
	{
		font = new Font();
		font->load("Fonte/Arial.ttf", 16);
	}

	void onDestroy()
	{
		delete font;
	}

	void render()
	{
		// OpenGL animation code goes here

		glClearColor( 0.3f, 0.3f, 0.3f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		glColor3f(1.0f, 0.5f, 0.0f);
		font->displayText(0, 0, "texto %d", 3);
		glColor3f(0.0f, 0.5f, 1.0f);
		font->displayText((getWidth() - font->textWidth("OpenGL TrueType Fonts")) / 2,
						  (getHeight() - font->textHeight()) / 2,
						  "OpenGL TrueType Fonts");
		glColor3f(0.5f, 1.0f, 0.5f);
		font->displayText(getWidth() - font->textWidth("FPS: %.2f", getFPS()),
						  getHeight() - font->textHeight(), "FPS: %.2f", getFPS());
		swapBuffers();
	}
};

int main(int argc, char *argv[])
{
	GLWindow mw;

	return mw.start(argc, argv);
}

