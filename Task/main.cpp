#include <thread>
#include <iostream>
#include <mutex>

#include "math.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
void calculateStep(float itemPosX1, float itemPosY1, float itemPosX2, float itemPosY2, float *stepX, float *stepY)
{
    float d, f, r, xa, ya, cnt;
    d = sqrt( pow( itemPosX2 - itemPosX1, 2 ) + pow( itemPosY2 - itemPosY1, 2 ) );//расстояние между центрами 2-х шариков
    r = fabs(50-d);//раcстояние между шариками
    if(d<50)
    {
        r = 0.9;//если один шарик добавить на другой, то оттолкнуть их
    }
    f = 1/r-1/pow(r,2);//Основная формула расчета
    //Расчет скорости притяжения шариков
    xa = itemPosX1 - itemPosX2;
    ya = itemPosY1 - itemPosY2;
    cnt = sqrt(xa*xa+ya*ya)/f;
    *stepX = xa/cnt;
    *stepY = ya/cnt;

    //return 0;
}

int threadMain(float itemPosX1, float itemPosY1, float itemPosX2, float itemPosY2, float *stepX, float *stepY)
{
    thread t(calculateStep, itemPosX1, itemPosY1, itemPosX2, itemPosY2, stepX, stepY);
    if(t.joinable())
    {
        t.join();
    }

    return 0;
}
