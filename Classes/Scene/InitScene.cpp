#include "InitScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/StartScene.h"

USING_NS_CC;

Scene* InitScene::createScene()
{
    return InitScene::create();
}

// on "init" you need to initialize your instance
bool InitScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*
    //add label
    auto label = Label::createWithTTF("Infinity2", "fonts/SmileySans-Oblique.ttf", 160);
    label->enableBold();
    label->setColor(Color3B(0x1E, 0x90, 0xFF));
    if (label == nullptr)
    {
        log("'fonts/SmileySans-Oblique.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    */

    //add back-image
    auto back_image = Sprite::create("infinity2.png");
    if (back_image == nullptr)
    {
        log("'infinity2,png'");
    }
    else
    {
        // position the label on the center of the screen
        back_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        // add the label as a child to this layer
        this->addChild(back_image, 1);
    }

    //replace after 2s
    auto delay = DelayTime::create(3.0f);
    auto callFunc = CallFunc::create(CC_CALLBACK_0(InitScene::replaceStartScene, this));
    auto sequence = Sequence::create(delay, callFunc, nullptr);
    this->runAction(sequence);

    return true;
}

void InitScene::replaceStartScene()
{
    Director::getInstance()->replaceScene(TransitionFadeTR::create(2.0f, StartScene::createScene()));
}
