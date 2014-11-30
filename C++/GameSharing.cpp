/*
GameSharing.cpp

Copyright 2014 Adrian Dawid

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


#include "GameSharing.h"

USING_NS_CC;

bool GameSharing::bIsGPGAvailable = true;
bool GameSharing::wasGPGAvailableCalled = false;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

std::map<int,std::string> GameSharing::iosLeaderboardIds = std::map<int,std::string>();
std::map<int,std::string> GameSharing::iosAchievementIds = std::map<int,std::string>();
int GameSharing::numberOfAchievements = 0;
int GameSharing::numberOfLeaderboards = 0;

#endif

void GameSharing::initGameSharing(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    ValueMap ids = FileUtils::getInstance()->getValueMapFromFile("ios_ids.plist");
    ValueVector aIds = ids.at("Achievements").asValueVector();
    ValueVector lIds = ids.at("Leaderboards").asValueVector();
    for (int i=0;i<aIds.size();i++) {
        iosAchievementIds[i] = aIds.at(i).asString();
        numberOfAchievements=i+1;
    }
    for (int i=0;i<lIds.size();i++) {
        iosLeaderboardIds[i] = lIds.at(i).asString();
        numberOfLeaderboards=i+1;
    }
    signInPlayer();
#endif
    
}

void GameSharing::SubmitScore(int score,int leaderboardID)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(IsGPGAvailable()){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "openLeaderboard"
                                           , "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, leaderboardID);
            
        }
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "submitScoreToLeaderboard"
                                           , "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
        }
    }
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    submitScoreToLeaderboard(score,leaderboardID);
#endif
}

void GameSharing::ShowLeaderboards(int id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(IsGPGAvailable()){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "openLeaderboard"
                                           , "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, id);
        }
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "openLeaderboardUI"
                                           , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
    else{
        errorHandler();
    }
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    openGameCenterLeaderboardsUI(id);
#endif
}

void GameSharing::UnlockAchivement(int ID)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(IsGPGAvailable())
    {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "openAchievement"
                                           , "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID , ID);
        }
        JniMethodInfo tmp;
        if (JniHelper::getStaticMethodInfo(tmp
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "updateAchievement"
                                           , "(I)V"))
        {
            tmp.env->CallStaticVoidMethod(tmp.classID, tmp.methodID , 100);
        }
    }
    else{
        errorHandler();
    }
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    unlockAchievement(ID);
#endif
}

void GameSharing::ShowAchievementsUI(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(IsGPGAvailable()){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "showAchievements"
                                           , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
    else{
        errorHandler();
    }
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    openAchievementUI();
#endif
}

bool GameSharing::IsGPGAvailable(){
    bool tmp = false;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/cpp.AppActivity"
                                       , "isGPGSupported"
                                       , "()Z"))
    {
        tmp = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
    }
#endif
    return tmp;
}

void GameSharing::ExitGame(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/cpp.AppActivity"
                                       , "exitGame"
                                       , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#else
    Director::getInstance()->end();
#endif
}


void GameSharing::ActivateStdErrorHandler(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    SetErrorHandler([]() -> void{
        MessageBox("A problem with Google Play Games was encounterd.", "Error");
        return;
    });
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    SetErrorHandler([]() -> void{
        MessageBox("A problem with Game Center was encounterd.", "Error");
        return;
    });
#endif
}

void GameSharing::SetErrorHandler(std::function<void ()> handler){
    errorHandler = handler;
}