#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "camera.h"
#include "object.h"
#include "vertex.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 4
#define DIR_DOWN 8

class MoveAction
{
public:
	virtual bool move(const Object& obj) = 0;
};

class Player: public Camera, public Object
{
private:
	Vertex trans;
	Vertex prior;
	int x_dir, y_dir;
	int x_state, y_state;
	float acceleration, velocity_limit, breaking_accel;
	float velocity_x, velocity_y;
	bool constant_velocity;
	int curr_x_dir, curr_y_dir;
	MoveAction* move_action;
private:
	
	bool checkMove()
	{
		if(move_action != NULL && trans != prior)
		{
			if(!move_action->move(*this))
			{
				trans = prior;
				return false;
			}
		}
		prior = trans;
		return true;
	}
	
public:
	Player(GLWindowBase * window);

	void setMoveAction(MoveAction* action);

	inline float getXDist()
	{
		return trans[0];
	}

	inline float getYDist()
	{
		return trans[1];
	}

	inline float getZDist()
	{
		return trans[2];
	}

	inline bool setXDist(float dx)
	{
		float d = dx - trans[0];
		translate(d, 0.0f, 0.0f);
		trans[0] = dx;
		if(!checkMove())
		{
			translate(-d, 0.0f, 0.0f);
			return false;
		}
		return true;
	}

	inline bool setYDist(float dy)
	{
		float d = dy - trans[1];
		translate(0.0f, d, 0.0f);
		trans[1] = dy;
		if(!checkMove())
		{
			translate(0.0f, -d, 0.0f);
			return false;
		}
		return true;
	}

	inline bool setZDist(float dz)
	{
		float d = dz - trans[2];
		translate(0.0f, 0.0f, d);
		trans[2] = dz;
		if(!checkMove())
		{
			translate(0.0f, 0.0f, -d);
			return false;
		}
		return true;
	}

	inline void setAcceleration(float accel)
	{
		acceleration = accel;
	}

	inline void setBreakingAcceleration(float break_accel)
	{
		breaking_accel = break_accel;
	}

	inline void setVelocityLimit(float limit)
	{
		velocity_limit = limit;
		if(velocity_limit < velocity_x)
			velocity_x = velocity_limit;
		if(velocity_limit < velocity_y)
			velocity_y = velocity_limit;
	}

	inline void setConstantVelocity(bool constant)
	{
		constant_velocity = constant;
	}

	inline float getAcceleration()
	{
		return acceleration;
	}

	inline float getBreakingAcceleration()
	{
		return breaking_accel;
	}

	inline float getVelocityLimit()
	{
		return velocity_limit;
	}

	inline bool isConstantVelocity()
	{
		return constant_velocity;
	}
	
	inline bool isMoving()
	{
		return x_state != 0 || y_state != 0;
	}

	void updateState(int dir, bool release);
	void move();
	virtual void render() {}
	virtual float* getVertexes()
	{
		return NULL;
	}
	virtual unsigned int getVertexCount()
	{
		return 0;
	}
};
#endif

