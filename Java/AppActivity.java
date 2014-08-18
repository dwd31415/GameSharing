/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import your.app.id.*;
import android.os.Bundle;
import com.google.android.gms.games.Games;
import android.content.Context;
import android.util.Log;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import android.content.Intent;
import android.app.Activity;

public class AppActivity extends BaseGameActivity {
    static int currentID;
    static int currentAchievementID;
    static boolean gpgAvailable;
    
    static String[] leaderboardIDs;
    static String[] achievementIDs;
    static Context currentContext;
    
    @Override
    public void onSignInSucceeded(){
        gpgAvailable = true;
    }
    
    @Override
    public void onSignInFailed(){
        gpgAvailable = false;
    }
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        String leaderboardIdsRaw = getString(R.string.leaderboards);
        Log.v("GPG","Hello World");
        String achievementIdsRaw = getString(R.string.achievements);
        
        leaderboardIDs = leaderboardIdsRaw.split(";");
        achievementIDs =  achievementIdsRaw.split(";");
        
        currentContext = this;
        
        super.onCreate(savedInstanceState);
    }
    
    static public void openLeaderboard(int leaderboardID){
         currentID = leaderboardID;
    }
    
    /*@brief This function opens the leaderboards ui for an leaderboard id*/
    static public void openLeaderboardUI(){
        if(gpgAvailable){
                ((AppActivity)currentContext).runOnUiThread(new Runnable() {
            public void run() {
                ((AppActivity)currentContext).startActivityForResult(Games.Leaderboards.getLeaderboardIntent(((AppActivity)currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID]),2);
            }
                });
        }
    }
    
    static public boolean isGPGSupported(){
        return gpgAvailable;
    }
    
    static public void submitScoreToLeaderboard(int score)
    {
        if(gpgAvailable){
        Games.Leaderboards.submitScore(((AppActivity)currentContext).getGameHelper().getApiClient(),leaderboardIDs[currentID],score);
        updateAchievement(100);
        }
    }
    
    static public void showAchievements() {
        if(gpgAvailable){
        ((AppActivity)currentContext).runOnUiThread(new Runnable() {
            public void run() {
                ((AppActivity)currentContext).startActivityForResult(Games.Achievements.getAchievementsIntent(((AppActivity)currentContext).getGameHelper().getApiClient()), 5);
            }
        });
        }
    }
    
    static public void openAchievement(int achievementID){
        currentAchievementID = achievementID;
    }
    
    static public void updateAchievement(int percentage){
        if(gpgAvailable){
        Log.v("GPG",achievementIDs[currentAchievementID]);
       Games.Achievements.unlock(((AppActivity)currentContext).getGameHelper().getApiClient(), achievementIDs[currentAchievementID]);
        }
    }
    
}


