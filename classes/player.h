#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "camera.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 4
#define DIR_DOWN 8

class Player: public Camera
{
private:
    float x_trans, y_trans, z_trans;
    int x_dir, y_dir;
    int x_state, y_state;
    float acceleration, velocity_limit, velocity, breaking_accel;
    float velocity_x, velocity_y;
    bool constant_velocity;
    int curr_x_dir, curr_y_dir;
public:
    Player(GLWindowBase * window);
    
    inline float getXDist()
    {
        return x_trans;
    }
    
    inline float getYDist()
    {
        return y_trans;
    }
    
    inline float getZDist()
    {
        return z_trans;
    }
    
    inline void setXDist(float dx)
    {
        x_trans = dx;
    }
    
    inline void setYDist(float dy)
    {
        y_trans = dy;
    }
    
    inline void setZDist(float dz)
    {
        z_trans = dz;
    }
    
    inline void setAcceleration(float accel)
    {
        acceleration = accel;
    }
    
    inline void setBreakingAcceleration(float break_accel)
    {
        breaking_accel = break_accel;
    }
    
    inline void setVelocity(float vel)
    {
        velocity = vel;
    }

    inline void setVelocityLimit(float limit)
    {
        velocity_limit = limit;
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
    
    inline float getVelocity()
    {
        return velocity;
    }

    inline float getVelocityLimit()
    {
        return velocity_limit;
    }
    
    inline bool isConstantVelocity()
    {
        return constant_velocity;
    }
    
    void updateState(int dir, bool release);
    void move();
};
#endif

