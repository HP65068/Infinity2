#include "NullScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/InitScene.h"

USING_NS_CC;

Scene* NullScene::createScene()
{
    return NullScene::create();
}

// on "init" you need to initialize your instance
bool NullScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //replace after 2s
    auto delay = DelayTime::create(1.0f);
    auto callFunc = CallFunc::create(CC_CALLBACK_0(NullScene::replaceScene, this));
    auto sequence = Sequence::create(delay, callFunc, nullptr);
    this->runAction(sequence);

    return true;
}

void NullScene::replaceScene()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, InitScene::createScene()));
}
