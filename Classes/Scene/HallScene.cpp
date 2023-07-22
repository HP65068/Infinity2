#include "HallScene.h"
#include "SimpleAudioEngine.h"
#include "Sprite/Bullet/PlBullet.h"
#include "Scene/GameScene.h"

USING_NS_CC;

Scene* HallScene::createScene()
{
    return HallScene::create();
}

// on "init" you need to initialize your instance
bool HallScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   //background
    auto background = Sprite::create("board3.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background, 1);

    //add player
    this->player = PlTank::create();
    player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(player, 3);

    //add portal
    portal = Sprite::create();
    float x = visibleSize.width / 2;
    float y = visibleSize.height * 7 / 10;
    portal->setPosition(x, y);
    this->addChild(portal, 2);

    //auto spriteCache = SpriteFrameCache::sharedSpriteFrameCache();
    auto animation = Animation::create();
    //spriteCache->addSpriteFramesWithFile("portal.plist");
    char name[20] = { '\0' };
    for (int i = 0; i < 4; i++)
    {
        memset(name, 0, sizeof(name));
        sprintf(name, "portal%d.png", i + 1);
        animation->addSpriteFrameWithFile(name);
    }
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(kRepeatForever);
    auto animate = Animate::create(animation);
    portal->runAction(animate);
    
    //listen keyboard event
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(HallScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(HallScene::onKeyReleased, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    //schedule update
    this->scheduleUpdate();

    return true;
}

void HallScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_J:
        launchBullet();
        break;
    case EventKeyboard::KeyCode::KEY_F:
        if (portal->getBoundingBox().intersectsRect(player->getBoundingBox()))
        {
            //player->removeFromParentAndCleanup(true);
            Director::getInstance()->replaceScene(TransitionSlideInR::create(2.0f, GameScene::createScene()));
        }
        break;
    }

    keyMap[keyCode] = true;
}

void HallScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    keyMap[keyCode] = false;
}

void HallScene::update(float dt)
{
    auto keyW = EventKeyboard::KeyCode::KEY_W;
    auto keyA = EventKeyboard::KeyCode::KEY_A;
    auto keyS = EventKeyboard::KeyCode::KEY_S;
    auto keyD = EventKeyboard::KeyCode::KEY_D;
    if (keyMap[keyW])
    {
        player->moveForward();
    }
    if (keyMap[keyS])
    {
        player->moveBehind();
    }
    if (keyMap[keyA])
    {
        player->rotateL();
    }
    if (keyMap[keyD])
    {
        player->rotateR();
    }
}

void HallScene::launchBullet()
{
    auto position = player->getPosition();
    float rotate = -player->getRotation() + 90.0;
    auto bullet = PlBullet::create();
    bullet->setPosition(position);
    bullet->move(rotate);
    this->addChild(bullet, 3);
}
