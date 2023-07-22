#include "Enemy.h"
#include "Sprite/Bullet/EnemyBullet.h"
#include "Header/Tag.h"

const double PI = 3.1415926;

USING_NS_CC;

Enemy* Enemy::create()
{
	Enemy* enemy = new(std::nothrow) Enemy();
	if (enemy && enemy->initWithFile("enemy.png"))
	{
		enemy->autorelease();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::moveForward()
{
	float rotate = -getRotation() + 90.0;
	//log("%f\n", rotate);
	rotate = rotate * PI / 180;
	float x = speed * cos(rotate);
	float y = speed * sin(rotate);
	setPosition(getPosition() + Vec2(x, y));
}

void Enemy::moveBehind()
{
	float rotate = -getRotation() + 90.0;
	//log("%f\n", rotate);
	rotate = rotate * PI / 180;
	float x = speed * cos(rotate);
	float y = speed * sin(rotate);
	setPosition(getPosition() - Vec2(x, y));
}

void Enemy::rotateL()
{
	int rotate = int(getRotation()) % 360;
	//log("%d\n", rotate);
	setRotation(rotate - speed * 2);
}

void Enemy::rotateR()
{
	int rotate = int(getRotation()) % 360;
	//log("%d\n", rotate);
	setRotation(rotate + speed * 2);
}

void Enemy::launchBullet(float dt)
{
	auto position = this->getPosition();
	float rotate = -this->getRotation() + 90.0;
	auto bullet = EnemyBullet::create();
	bullet->setPosition(position);
	bullet->setRotation(this->getRotation() - 90);
	bullet->move(rotate);
	//bullet->setTag(PLBULLET);

	//add physics body
	auto physicsBody = PhysicsBody::createBox(bullet->getContentSize());
	physicsBody->setDynamic(false);
	//physicsBody->setContactTestBitmask(0x02);
	//physicsBody->setCategoryBitmask(0x01);
	//physicsBody->setCollisionBitmask(0xFF);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	physicsBody->setGroup(HITPL);
	bullet->setPhysicsBody(physicsBody);

	bullet->setTag(ENEMYBULLET);

	this->getParent()->addChild(bullet, 3);
}

bool Enemy::init()
{
	//initWithTexture(nullptr, Rect::ZERO);

	//randomize rotation
	int rotate = rand() % 360;
	this->setRotation(float(rotate));

	return true;
}