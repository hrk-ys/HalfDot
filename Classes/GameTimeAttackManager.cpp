//
//  GameTimeAttackManager.cpp
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/06.
//
//

#include "GameTimeAttackManager.h"


float GameTimeAttackManager::getTime(float time) {
    gameTime += time;
    return gameTime;
}

bool GameTimeAttackManager::hasNextGame() {
    return levelVal+1 <= maxLevel;
}
