//
//  GameManager.h
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/06.
//
//

#ifndef __HalfDot__GameManager__
#define __HalfDot__GameManager__

#include <stdio.h>

class GameManager
{
protected:
    float gameTime;
    
public:
    int levelVal;
    
    GameManager(int level);
    
    virtual float getTime(float time);
    
    virtual bool hasNextGame();
};

#endif /* defined(__HalfDot__GameManager__) */
