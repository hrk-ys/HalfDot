//
//  WelcomeLayer.h
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/04.
//
//

#ifndef __HalfDot__WelcomeLayer__
#define __HalfDot__WelcomeLayer__

#include "cocos2d.h"

class WelcomeLayer : public cocos2d::Layer
{
private:
    void menuTimeTrack5Callback(cocos2d::Ref* pSender);
    void menuTimeTrack10Callback(cocos2d::Ref* pSender);
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(WelcomeLayer);
};

#endif /* defined(__HalfDot__WelcomeLayer__) */
