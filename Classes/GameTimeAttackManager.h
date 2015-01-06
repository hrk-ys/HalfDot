//
//  GameTimeAttackManager.h
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/06.
//
//

#ifndef __HalfDot__GameTimeAttackManager__
#define __HalfDot__GameTimeAttackManager__

#include <stdio.h>
#include "GameManager.h"

class GameTimeAttackManager : public GameManager
{
public:
    unsigned int maxLevel;
    
    GameTimeAttackManager(int level) : GameManager(level){
        this->maxLevel = level + 10;
    };
    
    virtual float getTime(float time);
    
    virtual bool hasNextGame();
};

#endif /* defined(__HalfDot__GameTimeAttackManager__) */
