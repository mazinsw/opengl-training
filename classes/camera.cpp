#include <GL/gl.h>
#include "camera.h"

Camera::Camera(GLWindowBase * window)
{
	this->window = window;
	old_x = window->getWidth() / 2;
	old_y = window->getHeight() / 2;
	window->setMousePos(old_x, old_y);
	window->showMouse(false);
	window->lockMouse(true);
	rot_x = rot_y = rot_z = 0.0f;
	min_x = 300.0f;
	max_x = 90.0f;
}

void Camera::updateAngle(int x, int y)
{
	rot_y += (float)(old_x - x) / window->getWidth() * 180.0f;
	rot_x += (float)(old_y - y) / window->getWidth() * 180.0f;

	if(rot_y > 360.0f)
		rot_y -= 360.0f;
	else if(rot_y < 0.0f)
		rot_y += 360.0f;
	if(x <= window->getWidth() / 3 || x >= window->getWidth() * (2.0f / 3))
	{
		old_x = window->getWidth() / 2;
		window->setMousePos(old_x, y);
	}
	else
		old_x = x;
	if(rot_x > 360.0f)
		rot_x -= 360.0f;
	else if(rot_x < 0.0f)
		rot_x += 360.0f;
	//limit
	if(rot_x < min_x && rot_x > max_x)
	{
		if(min_x - rot_x > rot_x - max_x)
			rot_x = max_x;
		else
			rot_x = min_x;
	}
	if(y <= window->getHeight() / 3 || y >= window->getHeight() * (2.0f / 3))
	{
		old_y = window->getHeight() / 2;
		window->setMousePos(x, old_y);
	}
	else
		old_y = y;
}

void Camera::look()
{
	glRotatef(-rot_x, 1.0f, 0.0f, 0.0f);
	glRotatef(-rot_y, 0.0f, 1.0f, 0.0f);
	glRotatef(-rot_z, 0.0f, 0.0f, 1.0f);
}

