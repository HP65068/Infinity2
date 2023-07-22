#pragma once
#include "cocos2d.h"
#include "Sprite/Tank/PlTank.h"

class HallScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HallScene);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void update(float);

    void launchBullet();

private:
    PlTank* player;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

    cocos2d::Sprite* portal;
};