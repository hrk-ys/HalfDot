//
//  WelcomeLayer.cpp
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/04.
//
//

#include "WelcomeLayer.h"
#include "GameLayer.h"
#include "GameTimeAttackManager.h"

USING_NS_CC;
using namespace std;

Scene* WelcomeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeLayer::create();
    scene->addChild(layer);
    return scene;
}

bool WelcomeLayer::init()
{
    if (!Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    

    auto menuTimeAttack5String = Label::createWithTTF("Time Attack5", "fonts/Marker Felt.ttf", 64.0f);
    auto menuTimeAttack5Label = MenuItemLabel::create(menuTimeAttack5String, CC_CALLBACK_1(WelcomeLayer::menuTimeTrack5Callback, this));
    menuTimeAttack5Label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 40.0f));
    
    auto menuTimeAttack10String = Label::createWithTTF("Time Attack10", "fonts/Marker Felt.ttf", 64.0f);
    auto menuTimeAttack10Label = MenuItemLabel::create(menuTimeAttack10String, CC_CALLBACK_1(WelcomeLayer::menuTimeTrack10Callback, this));
    menuTimeAttack10Label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 40.0f));
    
    auto menu = Menu::create(menuTimeAttack5Label, menuTimeAttack10Label, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

void WelcomeLayer::menuTimeTrack5Callback(cocos2d::Ref *pSender) {
    auto mgr = new GameTimeAttackManager(1);
    mgr->maxLevel=5;
    Scene* gameScene = (Scene*)GameLayer::createScene(mgr, 1);
    Director::getInstance()->replaceScene(gameScene);
}

void WelcomeLayer::menuTimeTrack10Callback(cocos2d::Ref *pSender) {
    auto mgr = new GameTimeAttackManager(1);
    mgr->maxLevel=10;
    Scene* gameScene = (Scene*)GameLayer::createScene(mgr, 1);
    Director::getInstance()->replaceScene(gameScene);
}