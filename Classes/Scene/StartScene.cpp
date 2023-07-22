#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/HallScene.h"
#include "Scene/CourseScene.h"
#include "Scene/SettingScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //add start label
    auto startLabel = Label::createWithTTF("Start", "fonts/SmileySans-Oblique.ttf", 72);
    auto startGame = MenuItemLabel::create(startLabel, CC_CALLBACK_1(StartScene::startEvent, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 9 * 7;
    startGame->setPosition(Vec2(x, y));

    //add help label
    auto helpLabel = Label::createWithTTF("Help", "fonts/SmileySans-Oblique.ttf", 72);
    auto helpItem = MenuItemLabel::create(helpLabel, CC_CALLBACK_1(StartScene::helpEvent, this));

    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 9 * 5;
    helpItem->setPosition(Vec2(x, y));

    //add setting label
    auto settingLabel = Label::createWithTTF("Setting", "fonts/SmileySans-Oblique.ttf", 72);
    auto settingItem = MenuItemLabel::create(settingLabel, CC_CALLBACK_1(StartScene::settingEvent, this));

    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 9 * 3;
    settingItem->setPosition(Vec2(x, y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startGame, helpItem, settingItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void StartScene::startEvent(Ref* pSender)
{
    Director::getInstance()->replaceScene(CCTransitionFade::create(2.0f, HallScene::createScene()));
}

void StartScene::helpEvent(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInB::create(1.0f, CourseScene::createScene()));
}

void StartScene::settingEvent(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInT::create(1.0f, SettingScene::createScene()));
}
