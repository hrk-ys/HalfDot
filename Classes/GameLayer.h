//
//  GameLayer.h
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/04.
//
//

#ifndef __HalfDot__GameLayer__
#define __HalfDot__GameLayer__

#include "cocos2d.h"
#include "GameManager.h"

enum GameType {
    TimeAttack
};

class GameLayer : public cocos2d::Layer
{
private:
    int dotNum;
    GameManager* gameManager;
    
    std::vector<cocos2d::Vec2> dots;
    
    cocos2d::EventListener* listener;
    
    void makeTimerLabel();
    void makeDot();
    void menuMenuBackCallback(cocos2d::Ref* pSender);
    
    void countTimer(float time);
    
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    
    cocos2d::Point lineStart;
    void setupLine(cocos2d::Point p);
    void movingLine(cocos2d::Point p);
    void finishLine(cocos2d::Point p);
    
    
    void nextLevel();
    void finishGame();
    
public:
    void setupWithLevel(int level);
    
    static cocos2d::Scene* createScene(GameManager* gameManager, int level);
    virtual bool init();
    

    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__HalfDot__GameLayer__) */
