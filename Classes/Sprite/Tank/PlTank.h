#pragma once
#include "cocos2d.h"

class PlTank :public cocos2d::Sprite
{
public:
	static PlTank* create();

	virtual bool init();

	void moveForward();
	void moveBehind();
	void rotateL();
	void rotateR();

	//return offset X
	float getOffsetX();

	//return offset Y
	float getOffsetY();

	//attributes
	int health = 10;
	int speed = 4;
	//int attack = 0;
	cocos2d::Vec2 mapPos;

private:
};

