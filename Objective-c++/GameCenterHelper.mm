/*
GameSharing.h

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

#import "GameSharing.h"
#import "AppController.h"
#import <GameKit/GameKit.h>


void GameSharing::openGameCenterLeaderboardsUI(int lId){
    NSLog(@"Open Leaderboard UI");
    if(iosLeaderboardIds.size() >= lId){
    if (![GKLocalPlayer localPlayer].isAuthenticated) {
        signInPlayer();
    }else{
    
            AppController* appController = (AppController*) [UIApplication sharedApplication].delegate;
    
            GKLeaderboardViewController* gkController = [[[GKLeaderboardViewController alloc] init] autorelease];
            gkController.leaderboardIdentifier = [NSString stringWithUTF8String:iosLeaderboardIds.at(lId).c_str()];
            gkController.timeScope = GKLeaderboardTimeScopeAllTime;
            gkController.timeScope = GKLeaderboardTimeScopeToday;
            gkController.leaderboardDelegate = appController.viewController;
        
            [appController.viewController presentModalViewController:gkController animated:YES];
        }
    }
}

void GameSharing::openAchievementUI(){
    NSLog(@"Open Achievements UI");
    
    if (![GKLocalPlayer localPlayer].isAuthenticated) {
        signInPlayer();
    }else{
            
        AppController* appController = (AppController*) [UIApplication sharedApplication].delegate;
            
        GKAchievementViewController* gkController = [[[GKAchievementViewController alloc] init] autorelease];
        gkController.achievementDelegate = appController;
            
        [appController.viewController presentModalViewController:gkController animated:YES];
    }
}

void GameSharing::submitScoreToLeaderboard(int score, int lId){
    if(iosLeaderboardIds.size() >= lId){
        GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier: [NSString stringWithUTF8String:iosLeaderboardIds.at(lId).c_str()]];
        scoreReporter.value = score;
        scoreReporter.context = 0;
    
        [GKScore reportScores:@[scoreReporter] withCompletionHandler:^(NSError *error) {
            if (error != nil) {
                NSLog(@"Error");
            }
        }];
    }
}

void GameSharing::unlockAchievement(int aId){
    if(iosLeaderboardIds.size() >= aId){
        GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier:
                                      [NSString stringWithUTF8String:iosAchievementIds.at(aId).c_str()]];
        if (achievement){
            achievement.percentComplete = 100;
            achievement.showsCompletionBanner = true;
            [GKAchievement reportAchievements:@[achievement] withCompletionHandler:^(NSError *error) {
                if (error != nil) {
                    NSLog(@"Error at GameSharing::unlockAchievement()");
                }
            }];
        }
    }
}

bool GameSharing::signInPlayer(){
    GKLocalPlayer *player = [GKLocalPlayer localPlayer];
    bool signedIn=false;
    [player authenticateWithCompletionHandler:^(NSError *error) {
            //Just relax and do nothing
    }];
    if (player.isAuthenticated) {
        signedIn = true;
    }
    return  signedIn;
}
