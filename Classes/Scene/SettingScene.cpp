#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/StartScene.h"
#include "ui/CocosGUI.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

USING_NS_CC;

Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //add return label
    auto returnLabel = Label::createWithTTF("Return", "fonts/SmileySans-Oblique.ttf", 48);
    auto returnItem = MenuItemLabel::create(returnLabel, CC_CALLBACK_1(SettingScene::returnEvent, this));
    float x = origin.x + visibleSize.width * 3 / 50;
    float y = origin.y + visibleSize.height * 2 / 50;
    returnItem->setPosition(Vec2(x, y));

    //add menu
    auto menu = Menu::create(returnItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //set background
    auto musicLabel = Label::createWithTTF("¿ªÆô±³¾°ÒôÀÖ", "fonts/SmileySans-Oblique.ttf", 48);
    musicLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 5 / 10));
    this->addChild(musicLabel, 1);

    auto checkbox = ui::CheckBox::create("check_box_normal.png", "check_box_active.png");
    checkbox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 4 / 10));
    checkbox->addEventListenerCheckBox(this, (ui::SEL_SelectedStateEvent)(&SettingScene::isBackGroundMusic));
    checkbox->setSelected(true);
    this->addChild(checkbox, 1);

    return true;
}

void SettingScene::returnEvent(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInB::create(1.0f, StartScene::createScene()));
}

void SettingScene::isBackGroundMusic(Ref* sender, ui::CheckBox::EventType type)
{
    auto fileIO = CCFileUtils::getInstance();
    switch (type)
    {
    case ui::CheckBox::EventType::SELECTED:
    {
        
        fileIO->writeStringToFile("1", "./config/config.ini");
        break;
    }
    case ui::CheckBox::EventType::UNSELECTED:
    {
        fileIO->writeStringToFile("0", "./config/config.ini");
        break;
    }
    }
}
