#include "object.h"
#include "util.h"
#include <stdio.h>

Object::Object()
{
	vq_count = 1;
	vq = new float[6 * vq_count];
	vq[0] = 0.5f;
	vq[1] = 0.5f;
	vq[2] = 0.5f;
	vq[3] = -0.5f;
	vq[4] = -0.5f;
	vq[5] = -0.5f;
}

Object::~Object()
{
	delete[] vq;
}

void Object::scale(float x, float y, float z)
{
	float * v;
	unsigned int i, count;

	count = getVertexCount();
	v = getVertexes();
	for(i = 0; i < count; i++)
	{
		v[0] *= x;
		v[1] *= y;
		v[2] *= z;
		v += 3;
	}
	v = vq;
	for(int j = 0; j < vq_count; j++)
	{
		v = vq + j * 6;
		for(i = 0; i < 2; i++)
		{
			v[0] *= x;
			v[1] *= y;
			v[2] *= z;
			v += 3;
		}
	}
}

void Object::translate(float x, float y, float z)
{
	float * v;
	unsigned int i, count;

	count = getVertexCount();
	v = getVertexes();
	for(i = 0; i < count; i++)
	{
		v[0] += x;
		v[1] += y;
		v[2] += z;
		v += 3;
	}
	v = vq;
	for(int j = 0; j < vq_count; j++)
	{
		v = vq + j * 6;
		for(i = 0; i < 2; i++)
		{
			v[0] += x;
			v[1] += y;
			v[2] += z;
			v += 3;
		}
	}
}

bool Object::collision(const Object& obj)
{
	bool test = false;
	float * v;
	for(int j = 0; j < vq_count && !test; j++)
	{
		v = vq + j * 6;
		test = (v[0] >= obj.vq[3] && v[3] <= obj.vq[0])
			   && (v[1] >= obj.vq[4] && v[4] <= obj.vq[1])
			   && (v[2] >= obj.vq[5] && v[5] <= obj.vq[2]);
	}
	return test;
}

void Object::refresh()
{
	float * v;
	unsigned int i, count;

	count = getVertexCount();
	v = getVertexes();
	if(count > 0)
	{
		// max
		vq[0] = v[0];
		vq[1] = v[1];
		vq[2] = v[2];
		// min
		vq[3] = v[0];
		vq[4] = v[1];
		vq[5] = v[2];
		v += 3;
	}
	for(i = 1; i < count; i++)
	{
		// max
		if(v[0] > vq[0])
			vq[0] = v[0];
		if(v[1] > vq[1])
			vq[1] = v[1];
		if(v[2] > vq[2])
			vq[2] = v[2];
		// min
		if(v[0] < vq[3])
			vq[3] = v[0];
		if(v[1] < vq[4])
			vq[4] = v[1];
		if(v[2] < vq[5])
			vq[5] = v[2];
		v += 3;
	}
}
