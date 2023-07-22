#include "EnemyBullet.h"

const double PI = 3.1415926;

USING_NS_CC;

EnemyBullet* EnemyBullet::create()
{
	EnemyBullet* bullet = new(std::nothrow) EnemyBullet();
	if (bullet && bullet->initWithFile("enemybullet.png"))
	{
		bullet->autorelease();
		return bullet;
	}

	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void EnemyBullet::move(float rotate)
{
	rotate = rotate * PI / 180;
	float x = speed * cos(rotate);
	float y = speed * sin(rotate);
	Vec2 destination(x, y);
	destination.normalize();
	destination *= 1200;
	auto moveAction = MoveBy::create(2.5f, destination);
	auto removeAction = RemoveSelf::create();
	this->runAction(Sequence::create(moveAction, removeAction, nullptr));
}