#pragma once
#include "cocos2d.h"

class Enemy :public cocos2d::Sprite
{
public:
	static Enemy* create();

	virtual bool init();

	void moveForward();
	void moveBehind();
	void rotateL();
	void rotateR();

	void launchBullet(float);

	//attributes
	int health = 1;
	int speed = 3;
	//int attack = 0;

private:
};