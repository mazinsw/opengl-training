#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <gl/gl.h>
#include "../classes/glwindow.h"
#include "../classes/random.h"
#include "../classes/display.h"
#define STAR_COUNT 2000

class Star
{
private:
    GLfloat x;
    GLfloat y;
    GLfloat velocity;
public:
    Star()
    {
        x = Random::range(-1.0f, 1.0f);
        y = Random::range(-1.0f, 1.0f);
        velocity = Random::range(0.001f, 0.02f);
    }
    void render()
    {
        glBegin( GL_POINTS );
        glColor3ub(255, 255, 255);
        glVertex2f(x, y);
        glEnd();
        x -= velocity;
        if(x < -1.0f)
            x = 1.0f;
    }

};

class GLWindow: public GLWindowBase
{
private:
    std::vector<Star*> stars;
    char str[50];
protected:
    void onCreate()
    {
        unsigned int i;

        Random::sort();
        for(i = 0; i < STAR_COUNT; i++)
        {
            stars.push_back(new Star());
        }
        setFrameRate(60);
    }

    void getWindowInfo(int & width, int & height, int & bpp,
                                 bool & fullScreen)
    {
        width = Display::getWidth();
        height = Display::getHeight();
        bpp = 32;
        fullScreen = true;
    }

    void onDestroy()
    {
        unsigned int i;
        Star * star;

        for(i = 0; i < stars.size(); i++)
        {
            star = stars[i];
            delete star;
        }
    }
    void render()
    {
        std::vector<Star*>::iterator ite;
        Star * star;
        
        // OpenGL animation code goes here
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        glPushMatrix();
        for(ite = stars.begin(); ite != stars.end(); ite++)
        {
            star = *ite;
            star->render();
        }
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

