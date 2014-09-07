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
#include <map>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#endif

class GameSharing{
public:
    /**@brief This function must be called on iOS, for it calls the signInPlayer() function,
     it has no effect on android, so don't call it if your app only runs on android*/
    static void initGameSharing();
    /**@brief This method submits a score to the current leaderboard*/
    static void SubmitScore(int score,int leaderboardId = 0);
    /**@brief This method opens the leaderboards UI for the current board*/
    static void ShowLeaderboards(int leaderbaordID = 0);
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
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    /**@brief This function opens the sign in ui, if needed or shows the "Welcome back:..." banner*/
    static bool signInPlayer();
    /**@brief Don't call this function by yourself*/
    static void openGameCenterLeaderboardsUI(int leaderboardID);
    /**@brief Don't call this function by yourself*/
    static void submitScoreToLeaderboard(int score,int leaderboardID);
    /**@brief Don't call this function by yourself*/
    static void unlockAchievement(int achievementID);
    /**@brief Don't call this function by yourself*/
    static void openAchievementUI();
    /**@brief Don't use this variable by yourself*/
    static std::map<int,std::string> iosLeaderboardIds;
    /**@brief Don't use this variable by yourself*/
    static std::map<int,std::string> iosAchievementIds;
    
#endif
    
    
};

#endif /* defined(__PaperChase__GameSharing__) */
