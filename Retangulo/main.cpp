#include <stdlib.h>
#include <stdio.h>
#include <gl/gl.h>
#include "../classes/glwindow.h"

class GLWindow: public GLWindowBase
{
private:
    char str[50];
protected:
    void render()
    {
        // OpenGL animation code goes here

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glPushMatrix();
        glBegin( GL_QUADS );
        glColor3ub(255, 0, 0);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);
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

