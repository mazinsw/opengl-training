#ifndef _RANDOM_H_
#define _RANDOM_H_
#include <stdlib.h>
#include <time.h>

class Random
{
public:
    static void sort()
    {
        srand(time(NULL));    
    }
    
    static int rand()
    {
        return ::rand();    
    }
    
    static int range(int begin, int end)
    {
        int number;
        
        number = ::rand() % (end - begin);
        return begin + number;
    }
    
    static float range(float begin, float end)
    {
        int number;
        
        number = ::rand() % (int)(1000 * end - 1000 * begin);
        return begin + (float)number / 1000;
    }
};

#endif
