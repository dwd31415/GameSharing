//
//  GameSharing.cpp
//  PaperChase
//
//  Created by Adrian Dawid on 17.08.14.
//
//

#include "GameSharing.h"

USING_NS_CC;

void GameSharing::SubmitScore(int score)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
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
#else
    CCLOG("Submit to Leaderboards");
#endif
}

void GameSharing::ShowLeaderboards(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
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
#else
    CCLOG("Show Leaderboards");
#endif
}

void GameSharing::UnlockAchivement(int ID)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
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
        t.env->CallStaticVoidMethod(t.classID, t.methodID , 100);
        // Release
        t.env->DeleteLocalRef(t.classID);
    }
#else
    CCLOG("Unlock achivement");
#endif
}