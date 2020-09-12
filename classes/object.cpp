#include "object.h"
#include <stdio.h>
#include <string.h>

int Object::getFormat(const char * line)
{
    int space_count = 0;

    while(*line != '\0')
    {
        if(*line == ' ')
            space_count++;
        line++;
    }
    if(space_count == 3)
        return FACE_3V;
    return FACE_4V;
}

std::string Object::getLine(FILE* fp)
{
    std::string line;
    char ch;

    while(!feof(fp))
    {
        fread(&ch, sizeof(char), 1, fp);
        if(ch == '\n')
            break;
        line.push_back(ch);
    }
    return line;
}

Object::Object()
{
    list = 0;
}

Object::~Object()
{
    if(list > 0)
        destroyList();
}

bool Object::load(std::string file)
{
    FILE *fp;
    std::string line;
    const char * ptr;
    Vertex * v;
    Vertex * n;
    Face * f;
    std::vector<Vertex*> vertexes;
    std::vector<Vertex*> normals;
    std::vector<Face*> faces;

    fp = fopen(file.c_str(), "rb");
    if(fp == NULL)
        return false;

    while(!feof(fp))
    {
        line = getLine(fp);
        if(!line.empty())
        {
            ptr = line.c_str();
            switch(ptr[0])
            {
            case 'v':
                if(ptr[1] == 'n')
                {
                    n = new Vertex;
                    sscanf(ptr, "vn %f %f %f", &n->x, &n->y, &n->z);
                    normals.push_back(n);
                }
                else
                {
                    v = new Vertex;
                    sscanf(ptr, "v %f %f %f", &v->x, &v->y, &v->z);
                    vertexes.push_back(v);
                }
                break;
            case 'f':
                f = new Face;
                f->type = getFormat(ptr);
                if(f->type == FACE_3V)
                {
                    sscanf(ptr, "f %d//%d %d//%d %d//%d",
                           &f->v1, &f->num, &f->v2, &f->num, &f->v3, &f->num);
                }
                else
                {
                    sscanf(ptr, "f %d//%d %d//%d %d//%d %d//%d",
                           &f->v1, &f->num, &f->v2, &f->num, &f->v3, &f->num,
                           &f->v4, &f->num);
                }

                faces.push_back(f);
                break;
            }
        }
    }

    fclose(fp);

    if(list > 0)
        destroyList();
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    std::vector<Face*>::iterator fite;

    for(fite = faces.begin(); fite != faces.end(); fite++)
    {
        f = *fite;
        if(f->type == FACE_3V)
        {
            glBegin(GL_TRIANGLES);
            glNormal3fv((GLfloat*)normals[f->num - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v1 - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v2 - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v3 - 1]);
            glEnd();
        }
        else
        {
            glBegin(GL_QUADS);
            glNormal3fv((GLfloat*)normals[f->num - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v1 - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v2 - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v3 - 1]);
            glVertex3fv((GLfloat*)vertexes[f->v4 - 1]);
            glEnd();
        }
    }
    glEndList();

    std::vector<Vertex*>::iterator ite;
    for(ite = vertexes.begin(); ite != vertexes.end(); ite++)
        delete *ite;
    for(ite = normals.begin(); ite != normals.end(); ite++)
        delete *ite;
    for(fite = faces.begin(); fite != faces.end(); fite++)
        delete *fite;
    return true;
}

GLuint Object::getList()
{
    return list;
}

void Object::destroyList()
{
    glDeleteLists(list, 1);
    list = 0;
}

void Object::render()
{
    glCallList(list);
}






