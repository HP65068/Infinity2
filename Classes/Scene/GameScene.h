#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Sprite/Tank/PlTank.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void update(float);

    void launchBullet();

    bool onContactBegin(cocos2d::PhysicsContact& contact);

    void addEnemy(float);

    void returnHallEvent(Ref* pSender);

private:
    PlTank* player;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

    CocosDenshion::SimpleAudioEngine* audio;

    cocos2d::Label* healthLabel;
    cocos2d::Label* scoreLabel;
    cocos2d::Label* levelLabel;
    cocos2d::Label* illustrate;

    //map layer object
    cocos2d::TMXTiledMap* mapLayer;

    int score = 0;
};