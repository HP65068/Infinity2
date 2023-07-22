#include "CourseScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/StartScene.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

USING_NS_CC;

Scene* CourseScene::createScene()
{
    return CourseScene::create();
}

// on "init" you need to initialize your instance
bool CourseScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //add return label
    auto returnLabel = Label::createWithTTF("Return", "fonts/SmileySans-Oblique.ttf", 48);
    auto returnItem = MenuItemLabel::create(returnLabel, CC_CALLBACK_1(CourseScene::returnEvent, this));
    float x = origin.x + visibleSize.width * 3 / 50;
    float y = origin.y + visibleSize.height * 2 / 50;
    returnItem->setPosition(Vec2(x, y));

    //add menu
    auto menu = Menu::create(returnItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //add texts
    auto str = "W A S D 移动\n\nF 触发事件\n\nJ 攻击";
    auto textLabel = Label::createWithTTF(str, "fonts/SmileySans-Oblique.ttf", 72);
    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 2;
    textLabel->setPosition(x, y);
    this->addChild(textLabel, 1);

    return true;
}

void CourseScene::returnEvent(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInT::create(1.0f, StartScene::createScene()));
}
