#pragma once
#include "cocos2d.h"

class PlBullet :public cocos2d::Sprite
{
public:
	static PlBullet* create();

	//virtual bool init();

	//get attributes
	inline int getSpeed() { return this->speed; };
	inline int getAttack() { return this->attack; };

	//set attributes
	inline void setSpeed(int i) { this->speed = i; };
	inline void setAttack(int i) { this->attack = i; };

	void move(float rotate);

private:
	int speed = 6;
	int attack = 1;
};