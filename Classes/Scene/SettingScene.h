#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SettingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);

    void returnEvent(Ref* pSender);

    void isBackGroundMusic(Ref*, cocos2d::ui::CheckBox::EventType);
};