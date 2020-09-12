#include "util.h"
#include <GL/gl.h>

void drawCube()
{
	const GLfloat vertexes[8][3] =
	{
		{ -0.5f, -0.5f,  0.5f},
		{  0.5f, -0.5f,  0.5f},
		{  0.5f,  0.5f,  0.5f},
		{ -0.5f,  0.5f,  0.5f},
		{ -0.5f, -0.5f, -0.5f},
		{  0.5f, -0.5f, -0.5f},
		{  0.5f,  0.5f, -0.5f},
		{ -0.5f,  0.5f, -0.5f}
	};

	const GLfloat normals[6][3] =
	{
		{  0.0,  0.0,  2.0 },
		{  0.0,  0.0, -2.0 },
		{  0.0, -2.0,  0.0 },
		{  0.0,  2.0,  0.0 },
		{  2.0,  0.0,  0.0 },
		{ -2.0,  0.0,  0.0 }
	};

	glBegin(GL_QUADS);

	// Front face
	glNormal3fv(normals[0]);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[3]);

	// Back face
	glNormal3fv(normals[1]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[7]);
	glVertex3fv(vertexes[6]);

	// Top face
	glNormal3fv(normals[2]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[0]);

	// Bottom face
	glNormal3fv(normals[3]);
	glVertex3fv(vertexes[3]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[7]);

	// Right face
	glNormal3fv(normals[4]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[2]);

	// Left face
	glNormal3fv(normals[5]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[3]);
	glVertex3fv(vertexes[7]);

	glEnd();
}

void drawAxis()
{
	// eixo x
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f( 5.0f, 0.0f, 0.0f);
	glEnd();

	// eixo y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glVertex3f(0.0f,  5.0f, 0.0f);
	glEnd();

	// eixo z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glVertex3f(0.0f, 0.0f,  5.0f);
	glEnd();
}

// Verifica se um ponto está dentro do polígono
bool pt_in_poly(const Vertex& point, const float* v, int count) {
	bool  oddNodes = false;
	const float *p1, *p2;
	float x, y;

	x = point[0];
	y = point[2];
	p2 = &v[(count - 1) * 3];
	for(int i = 0; i < count; i++) {
		p1 = &v[i * 3];
		if (((p1[2] < y && p2[2] >= y) || (p2[2] < y && p1[2] >= y)) &&
			(p1[0] <= x || p2[0] <= x)) {
			if(p1[0] + (float)(y - p1[2]) / (p2[2] - p1[2]) * (p2[0] - p1[0]) < x)
				oddNodes = !oddNodes;
		}
		p2 = p1;
	}
	return oddNodes;
}