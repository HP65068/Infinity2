#include "PlBullet.h"

const double PI = 3.1415926;

USING_NS_CC;

PlBullet* PlBullet::create()
{
	PlBullet* bullet = new(std::nothrow) PlBullet();
	if (bullet && bullet->initWithFile("plbullet.png"))
	{
		bullet->autorelease();
		return bullet;
	}

	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void PlBullet::move(float rotate)
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
