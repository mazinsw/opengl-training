#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include "../classes/glwindow.h"
#include "../classes/display.h"

class GLWindow: public GLWindowBase
{
private:
    float theta;
    char str[50];
protected:
    virtual void getWindowInfo(int & width, int & height, int & bpp, 
        bool & fullscreen)
    {
    	// tamanho da janela para o tamanho do monitor
        width = Display::getWidth();
        height = Display::getHeight();
        // profundidade da cor
        bpp = 32;
        // determina se será exibido em tela cheia
        fullscreen = true;
    }
    
    virtual void onKeyDown(int key, int state)
    {
        GLWindowBase::onKeyDown(key, state);
        // ao pressionar 'r' a renderização fica mais leve
        // mas por outro lado fica com menos realismo
        if(key == SDLK_r)
            setFrameRate(30);
    }

    virtual void render()
    {
        // OpenGL animation code goes here

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glPushMatrix();
        glRotatef( theta, 0.0f, 0.0f, 1.0f );
        glBegin( GL_TRIANGLES );
        glColor3f( 1.0f, 0.0f, 0.0f );
        glVertex2f( 0.0f, 1.0f );
        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex2f( 0.87f, -0.5f );
        glColor3f( 0.0f, 0.0f, 1.0f );
        glVertex2f( -0.87f, -0.5f );
        glEnd();
        glPopMatrix();

        swapBuffers();
        theta += 1.0f;

        sprintf(str, "FPS: %.2f", getFPS());
        setTitle(str);
    }
public:
    GLWindow()
    {
        theta = 0.0f;
    }
};

int main(int argc, char *argv[])
{
    GLWindow mw;

    return mw.start(argc, argv);
}

