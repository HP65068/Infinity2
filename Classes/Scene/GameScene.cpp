#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Sprite/Bullet/PlBullet.h"
#include "Sprite/Tank/Enemy.h"
#include "Header/Tag.h"
#include "Scene/HallScene.h"
#include "ui/CocosGUI.h"
#include "fstream"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //load map
    mapLayer = TMXTiledMap::create("map/level1.tmx");
    mapLayer->setPosition(Vec2::ZERO);
    this->addChild(mapLayer);

    //add player
    this->player = PlTank::create();
    player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    player->setTag(PLTANK);
    //add physics body
    auto physicsBody = PhysicsBody::createBox(player->getContentSize());
    physicsBody->setDynamic(false);
    //physicsBody->setContactTestBitmask(0x01);
    //physicsBody->setCategoryBitmask(0x02);
    //physicsBody->setCollisionBitmask(0xFF);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    physicsBody->setGroup(HITPL);
    player->setPhysicsBody(physicsBody);

    this->addChild(player, Z_TANK);

    //listen keyboard event
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    //contact detection
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    //schedule update
    this->scheduleUpdate();

    //play background music
    audio = SimpleAudioEngine::getInstance();
    //auto fileIO = CCFileUtils::getInstance();
    //std::string str = fileIO->getStringFromFile("./config/config.ini");
    std::string str;
    std::ifstream inFile;
    inFile.open("./config/config.ini", std::ios::in);//打开文件
    inFile >> str;
    inFile.close();
    if (str == "1")
    {
        audio->playBackgroundMusic("music/bk.mp3", true);
    }

    //add enemy
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::addEnemy), 1.0f);

    //display level

    //create ttfconfig
    TTFConfig ttfConfig;
    ttfConfig.fontSize = 24;
    ttfConfig.fontFilePath = "fonts/SmileySans-Oblique.ttf";

    char * lv = new char[10];
    memset(lv, 0, sizeof(lv));
    sprintf(lv, "Level: %d", 1);
    levelLabel = Label::createWithTTF(ttfConfig, lv);
    levelLabel->setAnchorPoint(Vec2(0, 0));
    levelLabel->setPosition(visibleSize.width / 50, visibleSize.height / 50 * 48);
    levelLabel->setColor(Color3B(0x21, 0x96, 0xF3));
    this->addChild(levelLabel, Z_LABEL);
    delete lv;

    //display player's health
    char * hp = new char[10];
    memset(hp, 0, sizeof(hp));
    sprintf(hp, "HP: %d", player->health);
    healthLabel = Label::createWithTTF(ttfConfig, hp);
    healthLabel->setAnchorPoint(Vec2(0, 0));
    healthLabel->setPosition(visibleSize.width / 50, visibleSize.height / 50 * 46);
    healthLabel->setColor(Color3B(255, 0, 0));
    this->addChild(healthLabel, Z_LABEL);
    delete(hp);

    //display score
    char * sc = new char[10];
    memset(sc, 0, sizeof(sc));
    sprintf(sc, "Score: %d", this->score);
    scoreLabel = Label::createWithTTF(ttfConfig, sc);
    scoreLabel->setAnchorPoint(Vec2(0, 0));
    scoreLabel->setPosition(visibleSize.width / 50, visibleSize.height / 50 * 44);
    scoreLabel->setColor(Color3B(0x4C, 0xAF, 0x50));
    this->addChild(scoreLabel, Z_LABEL);
    delete(sc);

    //display level1 illustrate on the center screen
    str = "     Level 1\n消灭所有敌人";
    ttfConfig.fontSize = 72;
    illustrate = Label::createWithTTF(ttfConfig, str);
    illustrate->setPosition(visibleSize.width / 10 * 5, visibleSize.height / 10 * 4);
    illustrate->setColor(Color3B(0xFF, 0xC1, 0x07));
    this->addChild(illustrate, Z_LABEL);
    illustrate->setVisible(false);
    
    // 创建入场动画
    auto fadeIn = FadeIn::create(0.5f); // 淡入动画，持续时间为 0.5 秒
    auto moveIn = MoveBy::create(0.5f, Vec2(0, 100)); // 上移动画，持续时间为 0.5 秒
    auto fadeInMoveIn = Spawn::create(fadeIn, moveIn, nullptr); // 同时执行淡入和上移动画

    // 创建出场动画
    auto fadeOut = FadeOut::create(0.5f); // 淡出动画，持续时间为 0.5 秒
    auto moveOut = MoveBy::create(0.5f, Vec2(0, -100)); // 下移动画，持续时间为 0.5 秒
    auto fadeOutMoveOut = Spawn::create(fadeOut, moveOut, nullptr); // 同时执行淡出和下移动画
    auto visible = CallFunc::create([&]() {illustrate->setVisible(true); });

    // 创建动画序列，包括入场和出场动画
    auto sequence = Sequence::create(DelayTime::create(2.5f), visible, fadeInMoveIn,
        DelayTime::create(1.5f), fadeOutMoveOut, nullptr); // 2 秒后执行出场动画

    // 执行动画序列
    illustrate->runAction(sequence);

    // 在动画结束后，移除 Label
    this->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&]() {
        illustrate->removeFromParentAndCleanup(true);
        }), nullptr));
    
    return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_J:
        launchBullet();
        break;
    }

    keyMap[keyCode] = true;
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    keyMap[keyCode] = false;
}

void GameScene::update(float dt)
{
    //scroll map
    Vec2 pl_pos = player->getPosition();
    Vec2 mapLayerPos = mapLayer->getPosition();
    player->mapPos = pl_pos - mapLayerPos;
    if (pl_pos.x > WIDTH * 0.9)
    {
        if (player->mapPos.x > 1500)   goto pov_1;
        player->setPositionX(WIDTH * 0.9);
        int x = player->getOffsetX();
        x = (x > 0 ? x : -x);
        Vec2 map_pos = mapLayer->getPosition();
        mapLayer->setPosition(map_pos.x - x, map_pos.y);
    }
    else if (pl_pos.x < WIDTH * 0.1)
    {
        if (player->mapPos.x < 100)   goto pov_1;
        player->setPositionX(WIDTH * 0.1);
        int x = player->getOffsetX();
        x = (x > 0 ? -x : x);
        Vec2 map_pos = mapLayer->getPosition();
        mapLayer->setPosition(map_pos.x - x, map_pos.y);
    }
    pov_1:
    if (pl_pos.y > HEIGHT * 0.9)
    {
        if (player->mapPos.y > 1440)   goto over_test;
        player->setPositionY(HEIGHT * 0.9);
        int y = player->getOffsetY();
        y = (y > 0 ? y : -y);
        Vec2 map_pos = mapLayer->getPosition();
        mapLayer->setPosition(map_pos.x, map_pos.y - y);
    }
    else if (pl_pos.y < HEIGHT * 0.1)
    {
        if (player->mapPos.y < 80)   goto over_test;
        player->setPositionY(HEIGHT * 0.1);
        int y = player->getOffsetY();
        y = (y > 0 ? -y : y);
        Vec2 map_pos = mapLayer->getPosition();
        mapLayer->setPosition(map_pos.x, map_pos.y - y);
    }

    //if over the map bounding
    over_test:
    if (pl_pos.x > WIDTH) player->setPositionX(WIDTH);
    else if (pl_pos.x < 0) player->setPositionX(0);
    if (pl_pos.y > HEIGHT) player->setPositionY(HEIGHT);
    else if (pl_pos.y < 0) player->setPositionY(0);


    //test
    /*char xx[30];
    memset(xx, 0, sizeof(xx));
    sprintf(xx, "%f  %f", player->mapPos.x, player->mapPos.y);
    this->levelLabel->setString(xx);
    player->setPosition(player->getPosition());*/

    auto keyW = EventKeyboard::KeyCode::KEY_W;
    auto keyA = EventKeyboard::KeyCode::KEY_A;
    auto keyS = EventKeyboard::KeyCode::KEY_S;
    auto keyD = EventKeyboard::KeyCode::KEY_D;
    auto keyK = EventKeyboard::KeyCode::KEY_K;
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
    //if (keyMap[keyK])
    //{
    //    player->speed = 6;
    //}
}

void GameScene::launchBullet()
{
    auto position = player->getPosition() - mapLayer->getPosition();
    float rotate = -player->getRotation() + 90.0;
    auto bullet = PlBullet::create();
    bullet->setPosition(position);
    bullet->move(rotate);
    bullet->setTag(PLBULLET);

    //add physics body
    auto physicsBody = PhysicsBody::createBox(bullet->getContentSize());
    physicsBody->setDynamic(false);
    //physicsBody->setContactTestBitmask(0x04);
    //physicsBody->setCategoryBitmask(0x01);
    //physicsBody->setCollisionBitmask(0xFF);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    physicsBody->setGroup(HITENEMY);
    bullet->setPhysicsBody(physicsBody);

    mapLayer->addChild(bullet, Z_BULLET);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    char hp[15];
    char sc[15];
    if (nodeA && nodeB)
    {
        auto tagA = nodeA->getTag();
        auto tagB = nodeB->getTag();
        if ((tagA == ENEMY && tagB == PLBULLET) || (tagB == ENEMY && tagA == PLBULLET))
        {
            nodeA->removeFromParentAndCleanup(true);
            nodeB->removeFromParentAndCleanup(true);
            audio->playEffect("music/plb.wav", false, 0.5f);
            this->score++;
            memset(sc, 0, sizeof(sc));
            sprintf(sc, "Score: %d", this->score);
            scoreLabel->setString(sc);
        }
        else if ((tagA == PLTANK && tagB == ENEMYBULLET) || (tagA == ENEMYBULLET && tagB == PLTANK))
        {
            if (tagA == PLTANK)
            {
                player->health--;
                nodeB->removeFromParentAndCleanup(true);
            }
            else
            {
                player->health--;
                nodeA->removeFromParentAndCleanup(true);
            }
            memset(hp, 0, sizeof(hp));
            sprintf(hp, "HP: %d", player->health);
            healthLabel->setString(hp);
            audio->playEffect("music/hurt.wav", false, 0.5f);
            //auto blink = Blink::create(0.1f, 1);          
            //player->runAction(blink);
            if (player->health <= 0)
            {
                Director::getInstance()->pause();
                auto button = Button::create("start.png");
                auto visibleSize = Director::getInstance()->getVisibleSize();
                button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
                //button->setTitleText("返回大厅");
                button->addTouchEventListener(CC_CALLBACK_1(GameScene::returnHallEvent, this));
                this->addChild(button, Z_BUTTON);
            }
        }
        //log("%d  %d\n", tagA, tagB);
    }

    return true;
}

void GameScene::addEnemy(float)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int x = rand() % int(visibleSize.width*1.9);
    int y = rand() % int(visibleSize.height*1.9);
    auto enemy = Enemy::create();
    enemy->init();
    enemy->setPosition(x, y);
    enemy->setTag(ENEMY);

    //add physics body
    auto physicsBody = PhysicsBody::createBox(enemy->getContentSize());
    physicsBody->setDynamic(false);
    //physicsBody->setContactTestBitmask(0x04);
    //physicsBody->setCategoryBitmask(0x01);
    //physicsBody->setCollisionBitmask(0xFF);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    physicsBody->setGroup(HITENEMY);
    enemy->setPhysicsBody(physicsBody);

    mapLayer->addChild(enemy, Z_TANK);

    enemy->schedule(CC_SCHEDULE_SELECTOR(Enemy::launchBullet), 0.5f);
}

void GameScene::returnHallEvent(Ref* pSender)
{
    //player->removeFromParentAndCleanup(true);
    audio->stopBackgroundMusic();
    audio->stopAllEffects();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(2.0f, HallScene::createScene()));
}
