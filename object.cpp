#include "baseTypes.h"
#include "collInfo.h"
#include "Object.h"
#include <math.h>

ObjectC::ObjectC(float initPosX, float initPosY, float initVelX, float initVelY)
{
    mPosition.x = initPosX;
    mPosition.y = initPosY;
    mVelocity.x = initVelX;
    mVelocity.y = initVelY;
};
ObjectC::ObjectC()
{
    mPosition.x = 0.0f;
    mPosition.y = 0.0f;
    mVelocity.x = 0.0f;
    mVelocity.y = 0.0f;
};
ObjectC::~ObjectC()
{
};

bool rectanglesCollide(float rect1Left, float rect1Top, float rect1Right, float reft1Bottom, float rect2Left, float rect2Top, float rect2Right, float rect2Bottom) {
	return (rect1Left < rect2Right) && (rect1Right > rect2Left) && (rect1Top > rect2Bottom) && (reft1Bottom < rect2Top);
}

double deg2rad (double degrees) {
    return degrees * 4.0 * atan (1.0) / 180.0;
}