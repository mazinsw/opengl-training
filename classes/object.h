#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <GL/gl.h>
#include <vector>
#include <string>

#define FACE_3V 0
#define FACE_4V 1

typedef struct
{
    GLfloat x, y, z;
} Vertex;

typedef struct
{
    unsigned char type;
    int num;
    int v1, v2, v3, v4;
} Face;

class Object
{
private:
    GLuint list;
    
    int getFormat(const char * line);
    std::string getLine(FILE *fp);
    GLuint genList();
public:
    Object();
    ~Object();
    bool load(std::string file);
    GLuint getList();
    void destroyList();
    void render();
};

#endif
