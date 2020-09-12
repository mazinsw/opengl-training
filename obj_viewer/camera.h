#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "classes/glwindow.h"

class Camera
{
protected:
	GLWindowBase * window;
private:
	float rot_y, rot_x, rot_z;
	int old_x, old_y;
	float min_x, max_x;
	float min_y, max_y;
	int skip_x, skip_y;
	bool skipmode;
public:
	Camera(GLWindowBase * window);

	inline float getXAngle()
	{
		return rot_x;
	}

	inline float getYAngle()
	{
		return rot_y;
	}

	inline float getZAngle()
	{
		return rot_z;
	}

	inline void setXAngle(float ax)
	{
		rot_x = ax;
	}

	inline void setYAngle(float ay)
	{
		rot_y = ay;
	}

	inline void setZAngle(float az)
	{
		rot_z = az;
	}

	void updateAngle(int x, int y);
	void look();
};
#endif

