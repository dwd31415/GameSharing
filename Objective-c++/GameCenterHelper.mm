//
//  GameCenterHelper.m
//
//  Created by Adrian Dawid on 30.08.14.
//
//

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