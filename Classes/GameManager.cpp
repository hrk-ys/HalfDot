//
//  GameManager.cpp
//  HalfDot
//
//  Created by Hiroki Yoshifuji on 2015/01/06.
//
//

#include "GameManager.h"

GameManager::GameManager(int level) {
    this->levelVal = level;
    this->gameTime = 0;
}

float GameManager::getTime(float time) {
    gameTime += time;
    return gameTime;
}

bool GameManager::hasNextGame() {
    return false;
}