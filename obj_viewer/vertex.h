#ifndef _VERTEX_H_
#define _VERTEX_H_
#define EPSILON 0.00001f
#define EQUAL(a, b) ((a) + EPSILON > (b) && (a) - EPSILON < (b))

class Vertex
{
private:
	float v[3];
protected:
	
public:
	Vertex();
	Vertex(const Vertex& ref);
	Vertex(float x, float y, float z);
	float& operator[](int pos);
	const float& operator[](int pos) const;
	const Vertex operator+(const Vertex& ref) const;
	const Vertex operator-(const Vertex& ref) const;
	const Vertex operator+(float right) const;
	const Vertex operator-(float right) const;
	const Vertex operator/(float right) const;
	const Vertex operator*(float right) const;
	Vertex& operator=(const Vertex& ref);
	Vertex& operator+=(const Vertex& ref);
	Vertex& operator-=(const Vertex& ref);
	Vertex& operator+=(float right);
	Vertex& operator-=(float right);
	Vertex& operator/=(float right);
	Vertex& operator*=(float right);
	bool operator==(const Vertex& right) const;
	bool operator!=(const Vertex& right) const;
	void normalize();
};

const Vertex operator+(float right, const Vertex &ref);
const Vertex operator-(float right, const Vertex &ref);
const Vertex operator/(float right, const Vertex &ref);
const Vertex operator*(float right, const Vertex &ref);

#endif /* _VERTEX_H_ */