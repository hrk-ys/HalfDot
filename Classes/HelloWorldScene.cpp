#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
//using namespace std;

enum {
    kTagTimerLabel = 100,
    kTagHighScoreLabel = 200,
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 変数初期化
    nextNumber = 1;
    gameTime = 0;
    srand((unsigned)time(NULL));
    
    // シングルタッチイベントリスナーを作成する。
    auto listener = EventListenerTouchOneByOne::create();
    // スワロータッチモードにするとonTouchBeganメソッドはタッチイベントは他では使われない。
    listener->setSwallowTouches(true);
    // onTouchBeganイベントコールバック関数実装のラムダ式の例
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener1 = listener;
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
//    listener1->onTouchBegan = [](Touch* touch, Event* event) {
//        // event->getCurrentTarget() は、リスナーのsceneGraphPriorityの優先順に対象オブジェクトを返す。
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
//        
//        // ボタンに対する相対的な位置を取得する。
//        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//        // コンテンツのサイズを取得する。
//        Size s = target->getContentSize();
//        // コンテンツ矩形を作成する。
//        Rect rect = Rect(0, 0, s.width, s.height);
//        
//        // クリックエリアをチェックする。
//        if (rect.containsPoint(locationInNode))
//        {
//            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
//            // 不透明度を変更する。
//            target->setOpacity(180);
//            return true;
//        }
//        return false;
//    };
    
    makeButtons();
    makeTimerLabel();
    makeHighScoreLabel();
    this->schedule(schedule_selector(HelloWorld::countTimer));
    
    /*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    cocos2d::JumpBy* move = cocos2d::JumpBy::create(2.0f, Vec2(visibleSize.width/2, 0), 20, 3 );
    sprite->runAction(move);
    
    cocos2d::FadeOut* fade = cocos2d::FadeOut::create(3);
    sprite->runAction(fade);
     */
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuRetryButton(cocos2d::Ref *pSender)
{
    _eventDispatcher->removeEventListener(listener1);
    Scene* gameScene = (Scene*)HelloWorld::createScene();
    Director::getInstance()->replaceScene(gameScene);
}

#pragma mark - タッチイベント

bool HelloWorld::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    log("onTouchBegin");
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    log("onTouchEnded");
    
    auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
    
    Point touchPoint = target->convertToNodeSpace(pTouch->getLocation());
    
    Node* node = this->getChildByTag(nextNumber);
    
    if (node->getBoundingBox().containsPoint(touchPoint) ) {
        
        Sprite* button = Sprite::create("backside.png");
        button->setPosition(node->getPosition());
        button->setTag(nextNumber);
        this->addChild(button);
        
        node->removeFromParentAndCleanup(true);
        
            
        if (nextNumber >= 5) {
            afterGame();
            return;
        }
        
        nextNumber++;
    }
}

void HelloWorld::makeButtons()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    log("w:%f, h:%f", visibleSize.width, visibleSize.height);
    log("x:%f, y:%f", origin.x, origin.y);
    
    float baseX = visibleSize.width/2 - 128*5/2;
    float baseY = visibleSize.height/2 - 128*5/2;
    
    //変数配列を初期化する
    std::vector<int> numbers;
    for (int i = 1; i <= 25; i++)
        numbers.push_back(i);
    
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            int index = rand() % numbers.size();
            
            
            // カードを生成する
            std::string fileName = StringUtils::format("frontside%02d.png", numbers.at(index));
            Sprite* button = Sprite::create(fileName.c_str());
            button->setPosition(Vec2((x+0.5)*128+baseX, (y+0.5)*128+baseY));
            button->setTag(numbers.at(index));
                           
            this->addChild(button);
            
            numbers.erase(numbers.begin() + index);

        }
    }
}

void HelloWorld::makeTimerLabel()
{
    // タイマーを表示
    
    TTFConfig ttfConfig("", 32.0f);
    Size bgSize = Director::getInstance()->getWinSize();
    Label* timerLabel = Label::createWithTTF("0.000s", "fonts/Marker Felt.ttf", 32.0f);
    timerLabel->setPosition(Vec2(bgSize.width*0.9f, bgSize.height * 0.9f));
    timerLabel->setTag(kTagTimerLabel);
    this->addChild(timerLabel);
}

void HelloWorld::makeHighScoreLabel()
{
    float highScore = UserDefault::getInstance()->getFloatForKey("highscore", 99.999f);
    
    // 以前のハイスコアを表示
    Size bgSize = Director::getInstance()->getWinSize();
    std::string highScoreString = StringUtils::format("%8.3fs", highScore);
    Label* highScoreLabel = Label::createWithTTF(highScoreString.c_str(), "fonts/Marker Felt.ttf", 32.0f);
    highScoreLabel->setPosition(Vec2(bgSize.width * 0.9f, bgSize.height * 0.1f));
    highScoreLabel->setTag(kTagHighScoreLabel);
    this->addChild(highScoreLabel);
}

void HelloWorld::countTimer(float time)
{
    gameTime += time;
    
    // 時間を表示する
    std::string timeString = StringUtils::format("%8.3fs", gameTime);
    Label* timerLabel = (Label*)this->getChildByTag(kTagTimerLabel);
    timerLabel->setString(timeString.c_str());
}

void HelloWorld::afterGame()
{
    // タイマー停止
    this->unschedule(schedule_selector(HelloWorld::countTimer));
    
    // 以前のハイスコアを取得
    float highScore = UserDefault::getInstance()->getFloatForKey("highscore", 99.999f);
    if (highScore > gameTime) {
        // ハイスコアを記録
        UserDefault::getInstance()->setFloatForKey("highscore", gameTime);
        UserDefault::getInstance()->flush();
        
        // ハイスコアを表示
        std::string highScoreString = StringUtils::format("%8.3fs", gameTime);
        Label* highScoreLabel = (Label*)this->getChildByTag(kTagHighScoreLabel);
        highScoreLabel->setString(highScoreString.c_str());
    }
    
    // リトライボタンを表示
    Size bgSize = Director::getInstance()->getWinSize();
    auto retryLabel = MenuItemFont::create("Retry", CC_CALLBACK_1(HelloWorld::menuRetryButton, this));
    retryLabel->setPosition(Vec2(bgSize.width*0.9f, bgSize.height * 0.2f));
    
    auto menu = Menu::create(retryLabel, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
}
