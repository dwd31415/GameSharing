//
//  GameSharing.cpp
//  Copyright (c) Adrian Dawid 2014
//
//  Created by Adrian Dawid on 17.08.14.
//
//

#include "GameSharing.h"

USING_NS_CC;

bool GameSharing::bIsGPGAvailable = true;
bool GameSharing::wasGPGAvailableCalled = false;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

std::map<int,std::string> GameSharing::iosLeaderboardIds = std::map<int,std::string>();
std::map<int,std::string> GameSharing::iosAchievementIds = std::map<int,std::string>();

#endif

void GameSharing::initGameSharing(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    ValueMap ids = FileUtils::getInstance()->getValueMapFromFile("ios_ids.plist");
    ValueVector aIds = ids.at("Achievements").asValueVector();
    ValueVector lIds = ids.at("Leaderboards").asValueVector();
    for (int i=0;i<aIds.size();i++) {
        iosAchievementIds[i] = aIds.at(i).asString();
    }
    for (int i=0;i<lIds.size();i++) {
        iosLeaderboardIds[i] = lIds.at(i).asString();
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
            // Release
            t.env->DeleteLocalRef(t.classID);
        }
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "submitScoreToLeaderboard"
                                           , "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
            // Release
            t.env->DeleteLocalRef(t.classID);
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
            // Release
            t.env->DeleteLocalRef(t.classID);
        }
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "openLeaderboardUI"
                                           , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            // Release
            t.env->DeleteLocalRef(t.classID);
        }
    }
    else{
        MessageBox("Google Play Games Services are not actvie.", "Error");
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
            // Release
            t.env->DeleteLocalRef(t.classID);
        }
        JniMethodInfo tmp;
        if (JniHelper::getStaticMethodInfo(tmp
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "updateAchievement"
                                           , "(I)V"))
        {
            tmp.env->CallStaticVoidMethod(tmp.classID, tmp.methodID , 100);
            // Release
            tmp.env->DeleteLocalRef(t.classID);
        }
    }
    else{
        MessageBox("Google Play Games Services are not actvie.", "Error");
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
            // Release
            t.env->DeleteLocalRef(t.classID);
        }
    }
    else{
        MessageBox("Google Play Games Services are not actvie.", "Error");
    }
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    openAchievementUI();
#endif
}

bool GameSharing::IsGPGAvailable(){
    bool tmp = false;
    if (!wasGPGAvailableCalled) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp.AppActivity"
                                           , "isGPGSupported"
                                           , "()Z"))
        {
            tmp = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
            // Release
            t.env->DeleteLocalRef(t.classID);
        }
#endif
        bIsGPGAvailable = tmp;
    }
    else{
        tmp = bIsGPGAvailable;
    }
    wasGPGAvailableCalled = true;
    return tmp;
}
