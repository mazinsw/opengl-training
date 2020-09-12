#ifndef _FONT_H_
#define _FONT_H_

//OpenGL Headers
#include <GL/gl.h>

struct CharInfo
{
    char ch;
    int width;
    int height;
};

class Font
{
public:
    Font();
    Font(const char * fontName, unsigned int height);
    ~Font();
    void load(const char * fontName, unsigned int height);
    int textHeight();
    int textWidth(const char *fmt, ...);
    void displayText(float x, float y, const char *fmt, ...);
private:
    float height;			///< Holds the height of the font.
    GLuint * textures;	///< Holds the texture id's
    CharInfo * charInfo;
    GLuint list_base;	///< Holds the first display list id
private:
    void pushMatrix();
    void popMatrix();
};

#endif

