#include "vertex.h"
#include <cmath>

Vertex::Vertex()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

Vertex::Vertex(const Vertex& ref)
{
	*this = ref;
}

Vertex::Vertex(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float& Vertex::operator[](int pos)
{
	return v[pos];
}

const float& Vertex::operator[](int pos) const
{
	return v[pos];
}

const Vertex Vertex::operator+(const Vertex& ref) const
{
	return Vertex(*this) += ref;
}

const Vertex Vertex::operator-(const Vertex& ref) const
{
	return Vertex(*this) -= ref;
}

const Vertex Vertex::operator+(float right) const
{
	return Vertex(*this) += right;
}

const Vertex Vertex::operator-(float right) const
{
	return Vertex(*this) -= right;
}

const Vertex Vertex::operator/(float right) const
{
	return Vertex(*this) /= right;
}

const Vertex Vertex::operator*(float right) const
{
	return Vertex(*this) *= right;
}

Vertex& Vertex::operator=(const Vertex& ref)
{
	v[0] = ref.v[0];
	v[1] = ref.v[1];
	v[2] = ref.v[2];
	return  *this;
}

Vertex& Vertex::operator+=(const Vertex& ref)
{
	v[0] += ref.v[0];
	v[1] += ref.v[1];
	v[2] += ref.v[2];
	return  *this;
}

Vertex& Vertex::operator-=(const Vertex& ref)
{
	v[0] -= ref.v[0];
	v[1] -= ref.v[1];
	v[2] -= ref.v[2];
	return  *this;
}

Vertex& Vertex::operator+=(float right)
{
	v[0] += right;
	v[1] += right;
	v[2] += right;
	return  *this;
}

Vertex& Vertex::operator-=(float right)
{
	v[0] -= right;
	v[1] -= right;
	v[2] -= right;
	return  *this;
}

Vertex& Vertex::operator/=(float right)
{
	v[0] /= right;
	v[1] /= right;
	v[2] /= right;
	return  *this;
}

Vertex& Vertex::operator*=(float right)
{
	v[0] *= right;
	v[1] *= right;
	v[2] *= right;
	return  *this;
}

bool Vertex::operator==(const Vertex& right) const
{
	return EQUAL(v[0], right.v[0]) && EQUAL(v[1], right.v[1]) && EQUAL(v[2], right.v[2]);
}

bool Vertex::operator!=(const Vertex& right) const
{
	return !(*this == right);
}

void Vertex::normalize()
{
	float length;
	
	length = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
	if(EQUAL(length, 0.0f))
		length = 1.0f;
	v[0] /= length;
	v[1] /= length;
	v[2] /= length;
}

const Vertex operator+(float right, const Vertex &ref)
{
	return ref + right;
}

const Vertex operator-(float right, const Vertex &ref)
{
	return ref - right;
}

const Vertex operator/(float right, const Vertex &ref)
{
	return ref / right;
}

const Vertex operator*(float right, const Vertex &ref)
{
	return ref * right;
}
