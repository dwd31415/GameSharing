/*
GameSharing.h

Copyright 2015 Adrian Dawid

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Created by Adrian Dawid on 17.08.14.

*/
#ifndef __GameSharing__
#define __GameSharing__

#include <iostream>
#include "cocos2d.h"
#include <map>
#include <functional>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#endif

class GameSharing{
public:
    /**@brief This function must be called on iOS, for it calls the signInPlayer() function,
     it has no effect on android, so don't call it if your app only runs on android*/
    static void initGameSharing(void *initObj);
    /**@brief This method submits a score to the current leaderboard*/
    static void SubmitScore(int score,int leaderboardId = 0);
    /**@brief This method opens the leaderboards UI for the current board*/
    static void ShowLeaderboards(int leaderbaordID = 0);
    /**@brief This method unlocks an achivement
     @param ID: The index of the achivement in your list.*/
    static void UnlockAchivement(int ID);
    /**@brief Shows the achievements window*/
    static void ShowAchievementsUI();
    /**@brief Closes the game, don't use Director::end() with GameSharing*/
    static void ExitGame();
    /**@brief Checks if GPG is available*/
    static bool IsGPGAvailable();
    /**@brief Sets the error handling method.*/
    static void SetErrorHandler(std::function<void()> handler);
    /**@brief Sets the error handling method.*/
    static void ActivateStdErrorHandler();
    /**@brief If the IsGPGAvailable method was called it is not requiered to call again.*/
    static bool wasGPGAvailableCalled;
    /**@brief Return value of the IsGPGAvaiblable function.*/
    static bool bIsGPGAvailable;
    /**@brief A function, that shall be called when an error is encountered.*/
    static std::function<void()> errorHandler;
    /**@brief Requests the current score from the leaderboard, if the 2nd argument is specified, the function pointer will be called once the request was answered.*/
    static void RequestCurrentScoreFromLeaderboard(int leaderboardID,std::function<void()> callback = NULL);
    /**@brief The score of the current player, THIS VALUE IS ONLY SET ONCE RequestCurrentScoreFromLeaderboard WAS CALLED.*/
    static int localPlayerScore;
    /**@brief Is the request being processed? If the process failed, the localPlayerScore is -1.*/
    static bool requestIsBeingProcessed;
    /**@brief The callback of the score request, it will be called on the main thread*/
    static std::function<void()> requestCallback;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    static void initGameSharing_iOS(void *initObj);
    /**@brief This function opens the sign in ui, if needed or shows the "Welcome back:..." banner*/
    static bool signInPlayer();
    /**@brief Don't call this function by yourself*/
    static void openGameCenterLeaderboardsUI(int leaderboardID);
    /**@brief Don't call this function by yourself*/
    static void startScoreRequest(int leaderboardID);
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
    /**@brief Number of Achievements used in this game*/
    static int numberOfAchievements;
    /**@brief Number of Leaderbaords used in this game*/
    static int numberOfLeaderboards;
    
#endif
    
    
};

#endif
