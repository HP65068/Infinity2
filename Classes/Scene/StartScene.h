#pragma once
#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

    void startEvent(Ref* pSender);
    void helpEvent(Ref* pSender);
    void settingEvent(Ref* pSender);
};