//
//  GameSharing.cpp
//  PaperChase
//
//  Created by Adrian Dawid on 17.08.14.
//
//

#include "GameSharing.h"

USING_NS_CC;

bool GameSharing::bIsGPGAvailable;
bool GameSharing::wasGPGAvailableCalled;

void GameSharing::SubmitScore(int score)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(IsGPGAvailable()){
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
#else
    CCLOG("Submit to Leaderboards");
#endif
}

void GameSharing::ShowLeaderboards(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(IsGPGAvailable()){
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
#else
    CCLOG("Show Leaderboards");
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
#else
    CCLOG("Unlock achivement");
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
#else
    CCLOG("Unlock achivement");
#endif
}

bool GameSharing::IsGPGAvailable(){
    bool tmp;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if(wasGPGAvailableCalled){
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
    wasGPGAvailableCalled = true;
    }else{
        tmp = bIsGPGAvailable;
    }
#endif
    bIsGPGAvailable = tmp;
    return tmp;
}