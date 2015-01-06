//
//  GameLayer.cpp
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/04.
//
//

#include "GameLayer.h"
#include "WelcomeLayer.h"

#define kWindowMergin 24

#define kTimerLabel   97
#define kDotNumLabel  99
#define kDotNode     100
#define kDotSize       8

#define kLineTag      98

USING_NS_CC;

Scene* GameLayer::createScene(GameManager* manager, int level)
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    layer->setupWithLevel(level);
    layer->gameManager = manager;
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    srand((unsigned)time(NULL));
    
    Size bgSize = Director::getInstance()->getWinSize();
    
    
    makeTimerLabel();
    this->schedule(schedule_selector(GameLayer::countTimer));
    
    // レベル
    auto levelLabel = Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 32.0f);
    levelLabel->setTag(kDotNumLabel);
    levelLabel->setAnchorPoint(Vec2(0, 1));
    levelLabel->setPosition(Vec2(kWindowMergin, bgSize.height-kWindowMergin));
    this->addChild(levelLabel);
    
    
    // メニューボタン
    auto menuBackLabel = MenuItemFont::create("menu", CC_CALLBACK_1(GameLayer::menuMenuBackCallback, this));
    menuBackLabel->setAnchorPoint(Vec2(1, 0));
    menuBackLabel->setPosition(Vec2(bgSize.width-kWindowMergin, kWindowMergin));
    
    
    auto menu = Menu::create(menuBackLabel, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    
    // イベント
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

#pragma mark - make view

void GameLayer::makeTimerLabel()
{
    // タイマーを表示
    Size bgSize = Director::getInstance()->getWinSize();
 
    auto timerLabel = Label::createWithTTF("0.000s", "fonts/Marker Felt.ttf", 32.0f);
    
    timerLabel->setAnchorPoint(Vec2(0, 1));
    timerLabel->setPosition(Vec2(kWindowMergin, bgSize.height-kWindowMergin-32));
    timerLabel->setTag(kTimerLabel);
    
    this->addChild(timerLabel);
}

void GameLayer::makeDot() {
   
    Size size = Director::getInstance()->getWinSize();
    size.width -= kWindowMergin*2;
    size.height -= kWindowMergin*2+32*3;
    
    for (int i=0; i<dotNum; i++) {
        auto draw = DrawNode::create();
        
        Vec2 p = Vec2(rand() % (int)size.width, rand() % (int)size.height);
        p.x += kWindowMergin;
        p.y += kWindowMergin+32;
        
        log("x:%d, y:%d", (int)p.x, (int)p.y);
        draw->setPosition(Vec2::ZERO);
        draw->setTag(i + kDotNode);
        this->addChild(draw);
        
        draw->drawDot(p, kDotSize, Color4F::WHITE);
        
        dots.push_back(p);
    }
}


void GameLayer::setupWithLevel(int level) {
    
    Label* levelLabel = (Label*)this->getChildByTag(kDotNumLabel);
    std::string levelString = StringUtils::format("Level: %d", level);
    levelLabel->setString(levelString.c_str());
    
    dotNum = level*2;
    
    makeDot();
}

void GameLayer::countTimer(float time) {
    
    // 時間を表示する
    std::string timeString = StringUtils::format("%.3fs", gameManager->getTime(time));
    Label* timerLabel = (Label*)this->getChildByTag(kTimerLabel);
    timerLabel->setString(timeString.c_str());
}

#pragma mark - menu

void GameLayer::menuMenuBackCallback(cocos2d::Ref *pSender)
{
    log("menu back");
    Scene* welcomeScene = (Scene*)WelcomeLayer::createScene();
    Director::getInstance()->replaceScene(welcomeScene);
}


#pragma mark - line

void GameLayer::setupLine(Point p) {
    lineStart = p;
}

void GameLayer::movingLine(Point p) {
    this->removeChildByTag(kLineTag);
    
    auto draw = DrawNode::create();
    
    draw->setPosition(Vec2::ZERO);
    draw->setTag(kLineTag);
    this->addChild(draw);
    
    draw->drawSegment(lineStart, p, 2, Color4F::YELLOW);
}

void GameLayer::finishLine(Point p) {
    
    float diffY = lineStart.y - p.y;
    float diffX = lineStart.x - p.x;
    
    int dotCount = 0;
    if (diffX == 0.0) {
         for (auto dot : dots) {
            log("x=%f, y=%f", dot.x, dot.y);
            if (p.x > dot.x) {
                dotCount++;
            }
        }
    } else {
        float a = diffY / diffX;
        float b = p.y - a * p.x;
        
        log("a=%f, b=%f", a, b);
        for (auto dot : dots) {
            log("x=%f, y=%f", dot.x, dot.y);
            float y = dot.x * a + b;
            log("ret y=%f", y);
            if (y > dot.y) {
                dotCount++;
            }
        }
    }
    
    if (dotCount == dotNum/2) {
        if (gameManager->hasNextGame()) {
            nextLevel();
        } else {
            finishGame();
        }
    }
}


#pragma mark - game next

void GameLayer::nextLevel()
{
    log("nextLevel");
    
    dots.clear();
    this->removeChildByTag(kLineTag);
    for (int i=0; i<dotNum; i++) {
        this->removeChildByTag(i + kDotNode);
    }

    gameManager->levelVal = gameManager->levelVal + 1;
    setupWithLevel(gameManager->levelVal);
}

void GameLayer::finishGame()
{
    log("finishGame");
    this->unschedule(schedule_selector(GameLayer::countTimer));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto finishLabel = Label::createWithTTF("Finish", "fonts/Marker Felt.ttf", 128.0f);
    finishLabel->setColor(Color3B::GREEN);
    finishLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(finishLabel);
}

#pragma mark - touch event

bool GameLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
    Point touchPoint = target->convertToNodeSpace(pTouch->getLocation());
    log("onTouchBegin x:%d, y:%d", (int)touchPoint.x, (int)touchPoint.y);
    
    setupLine(touchPoint);
    return true;
}
void GameLayer::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
    Point touchPoint = target->convertToNodeSpace(pTouch->getLocation());
    log("onTouchMoved x:%d, y:%d", (int)touchPoint.x, (int)touchPoint.y);
    
    movingLine(touchPoint);
}
void GameLayer::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
    Point touchPoint = target->convertToNodeSpace(pTouch->getLocation());
    log("onTouchEnded x:%d, y:%d", (int)touchPoint.x, (int)touchPoint.y);
    
    finishLine(touchPoint);
}

