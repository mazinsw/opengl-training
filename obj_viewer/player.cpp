#include "player.h"
#include <GL/gl.h>
#include <math.h>

Player::Player(GLWindowBase* window): Camera(window)
{
	trans[0] = trans[1] = trans[2] = 0.0f;
	x_dir = y_dir = 0;
	x_state = y_state = 0;
	acceleration = 0.003f;
	velocity_limit = 0.1f;
	velocity_x = velocity_y = 0.0f;
	breaking_accel = 0.003f;
	constant_velocity = true;
	curr_x_dir = curr_y_dir = 0;
	move_action = NULL;
}

void Player::setMoveAction(MoveAction* action)
{
	move_action = action;
}

void Player::updateState(int dir, bool release)
{
	if(!release)
	{
		switch(dir)
		{
		case DIR_RIGHT:
			x_state |= DIR_RIGHT;
			x_dir = 1;
			curr_x_dir = 1;
			break;
		case DIR_LEFT:
			x_state |= DIR_LEFT;
			x_dir = -1;
			curr_x_dir = -1;
			break;
		case DIR_UP:
			y_state |= DIR_UP >> 2;
			y_dir = 1;
			curr_y_dir = 1;
			break;
		case DIR_DOWN:
			y_state |= DIR_DOWN >> 2;
			y_dir = -1;
			curr_y_dir = -1;
			break;
		}
	}
	else
	{
		switch(dir)
		{
		case DIR_RIGHT:
			x_state &= ~DIR_RIGHT;
			x_dir = (x_state > 0) ? -1 : 0;
			if(x_dir != 0)
				curr_x_dir = x_dir;
			break;
		case DIR_LEFT:
			x_state &= ~DIR_LEFT;
			x_dir = (x_state > 0) ? 1 : 0;
			if(x_dir != 0)
				curr_x_dir = x_dir;
			break;
		case DIR_UP:
			y_state &= ~(DIR_UP >> 2);
			y_dir = (y_state > 0) ? -1 : 0;
			if(y_dir != 0)
				curr_y_dir = y_dir;
			break;
		case DIR_DOWN:
			y_state &= ~(DIR_DOWN >> 2);
			y_dir = (y_state > 0) ? 1 : 0;
			if(y_dir != 0)
				curr_y_dir = y_dir;
			break;
		}
	}
}

void Player::move()
{
	float x_angle, y_angle, x_trans, z_trans;

	x_trans = trans[0];
	z_trans = trans[2];
	/* calcula a velocidade */
	if(constant_velocity)
	{
		velocity_x = velocity_limit;
		velocity_y = velocity_limit;
	}
	else
	{
		/* está em movimento no eixo x */
		if(x_dir != 0)
		{
			if(velocity_x < velocity_limit)
			{
				if(velocity_x + acceleration > velocity_limit)
					velocity_x = velocity_limit;
				else
					velocity_x += acceleration;
			}
		}
		else if(velocity_x > 0)/* está parando */
		{
			if(velocity_x - breaking_accel > 0)
				velocity_x -= breaking_accel;
			else
			{
				velocity_x = 0.0f;
				curr_x_dir = 0;
			}
		}
		/* está em movimento no eixo y */
		if(y_dir != 0)
		{
			if(velocity_y < velocity_limit)
			{
				if(velocity_y + acceleration > velocity_limit)
					velocity_y = velocity_limit;
				else
					velocity_y += acceleration;
			}
		}
		else if(velocity_y > 0)/* está parando */
		{
			if(velocity_y - breaking_accel > 0)
				velocity_y -= breaking_accel;
			else
			{
				velocity_y = 0.0f;
				curr_y_dir = 0;
			}
		}
	}
	/* calcula a posição e move o objeto */
	y_angle = getYAngle() - 360.0f;
	if(y_angle < 0.0f)
		y_angle = -y_angle - 360.0f;
	if(curr_x_dir == 1)
	{
		x_trans += velocity_x * cos(2 * M_PI * y_angle / 360);
		z_trans += velocity_x * sin(2 * M_PI * y_angle / 360);
	}
	else if(curr_x_dir == -1)
	{
		x_trans -= velocity_x * cos(2 * M_PI * y_angle / 360);
		z_trans -= velocity_x * sin(2 * M_PI * y_angle / 360);
	}
	y_angle += 90.0f;
	x_angle = 0 - 360.0f;
	if(x_angle < 0.0f)
		x_angle = -x_angle - 360.0f;
	if(curr_y_dir == 1)
	{
		x_trans -= velocity_y * cos(2 * M_PI * y_angle / 360);
		z_trans -= velocity_y * sin(2 * M_PI * y_angle / 360);

		trans[1] -= velocity_y * sin(2 * M_PI * x_angle / 360);
	}
	else if(curr_y_dir == -1)
	{
		x_trans += velocity_y * cos(2 * M_PI * y_angle / 360);
		z_trans += velocity_y * sin(2 * M_PI * y_angle / 360);

		trans[1] += velocity_y * sin(2 * M_PI * x_angle / 360);
	}
	setXDist(x_trans);
	setZDist(z_trans);
	glTranslatef(-trans[0], -trans[1], -trans[2]);
}

