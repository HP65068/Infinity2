#include "PlTank.h"

const double PI = 3.1415926;

USING_NS_CC;

PlTank* PlTank::create()
{
	PlTank* pltank = new(std::nothrow) PlTank();
	if (pltank && pltank->initWithFile("pltank.png"))
	{
		pltank->autorelease();
		pltank->init();
		return pltank;
	}

	CC_SAFE_DELETE(pltank);
	return nullptr;
}

void PlTank::moveForward()
{
	float rotate = -getRotation() + 90.0;
	//log("%f\n", rotate);
	rotate = rotate * PI / 180;
	float x = speed * cos(rotate);
	float y = speed * sin(rotate);
	setPosition(getPosition() + Vec2(x, y));
}

void PlTank::moveBehind()
{
	float rotate = -getRotation() + 90.0;
	//log("%f\n", rotate);
	rotate = rotate * PI / 180;
	float x = speed * cos(rotate);
	float y = speed * sin(rotate);
	setPosition(getPosition() - Vec2(x, y));
}

void PlTank::rotateL()
{
	int rotate = int(getRotation()) % 360;
	//log("%d\n", rotate);
	setRotation(rotate - speed * 2);
}

void PlTank::rotateR()
{
	int rotate = int(getRotation()) % 360;
	//log("%d\n", rotate);
	setRotation(rotate + speed * 2);
}

float PlTank::getOffsetX()
{
	float rotate = -getRotation() + 90.0;
	rotate = rotate * PI / 180;
	float x = speed * cos(rotate);
	return x;
}

float PlTank::getOffsetY()
{
	float rotate = -getRotation() + 90.0;
	rotate = rotate * PI / 180;
	float y = speed * sin(rotate);
	return y;
}

bool PlTank::init()
{
	//give mapPos a specific value, avoid the circumstance it will be zero
	mapPos = Vec2(100, 100);
	return true;
}