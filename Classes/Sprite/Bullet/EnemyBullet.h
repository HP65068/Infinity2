#pragma once
#include "cocos2d.h"

class EnemyBullet :public cocos2d::Sprite
{
public:
	static EnemyBullet* create();

	//virtual bool init();

	//get attributes
	inline int getSpeed() { return this->speed; };
	inline int getAttack() { return this->attack; };

	//set attributes
	inline void setSpeed(int i) { this->speed = i; };
	inline void setAttack(int i) { this->attack = i; };

	void move(float rotate);

private:
	int speed = 5;
	int attack = 1;
};