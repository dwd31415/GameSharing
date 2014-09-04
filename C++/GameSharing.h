//
//  GameSharing.h
//  Copyright (c) Adrian Dawid 2014
//
//  Created by Adrian Dawid on 17.08.14.
//
//

#ifndef __PaperChase__GameSharing__
#define __PaperChase__GameSharing__

#include <iostream>
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#endif

class GameSharing{
public:
    /**@brief This method submits a score to the current leaderboard*/
    static void SubmitScore(int score);
    /**@brief This method opens the leaderboards UI for the current board*/
    static void ShowLeaderboards();
    /**@brief This method unlocks an achivement
       @param ID: The index of the achivement in your list.*/
    static void UnlockAchivement(int ID);
    /**@brief Shows the achievements window*/
    static void ShowAchievementsUI();
    /**@brief Checks if GPG is available*/
    static bool IsGPGAvailable();
    /**@brief If the IsGPGAvailable method was called it is not requiered to call again.*/
    static bool wasGPGAvailableCalled;
    /**@brief Return value of the IsGPGAvaiblable function.*/
    static bool bIsGPGAvailable;
};

#endif /* defined(__PaperChase__GameSharing__) */
