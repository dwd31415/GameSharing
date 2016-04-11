/*
 GameCenterHelper.mm
 
 Copyright 2016 Adrian Dawid
 
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
#import <GameKit/GameKit.h>

@interface GameCenterDelegate : NSObject<GKGameCenterControllerDelegate>
@property(nonatomic, weak) UIViewController *viewController;
@end

@implementation GameCenterDelegate

- (void) gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController {
    [self.viewController dismissViewControllerAnimated:YES completion:nil];
}

+ (GameCenterDelegate *) getInstance {
    static GameCenterDelegate *gameCenterDelegate = nil;
    if (gameCenterDelegate == nil) {
        gameCenterDelegate = [[GameCenterDelegate alloc] init];
    }
    return gameCenterDelegate;
}

@end

void GameSharing::initGameSharing_iOS(void *initObj) {
    GameCenterDelegate *tmp = [GameCenterDelegate getInstance];
    tmp.viewController = (__bridge UIViewController *)initObj;
}

void GameSharing::openGameCenterLeaderboardsUI(int lId){
    NSLog(@"Open Leaderboard UI");
    if(iosLeaderboardIds.size() >= lId){
        if (![GKLocalPlayer localPlayer].isAuthenticated) {
            if(!signInPlayer())
            {
                NSLog(@"Cannot open Leaderboard UI. Not logged in.");
                if (GameSharing::errorHandler != nullptr) {
                    GameSharing::errorHandler();
                }
            }
        }else{
            GKGameCenterViewController* gkController = [[GKGameCenterViewController alloc] init];
            gkController.leaderboardIdentifier = [NSString stringWithUTF8String:iosLeaderboardIds.at(lId).c_str()];
            gkController.leaderboardTimeScope = GKLeaderboardTimeScopeAllTime;

            GameCenterDelegate *gameCenterDelegate = [GameCenterDelegate getInstance];
            gkController.gameCenterDelegate = gameCenterDelegate;
            
            [gameCenterDelegate.viewController presentViewController:gkController animated:YES completion:^{}];
        }
    }
}

void GameSharing::openAchievementUI(){
    NSLog(@"Open Achievements UI");
    
    if (![GKLocalPlayer localPlayer].isAuthenticated) {
        if(!signInPlayer())
        {
            NSLog(@"Cannot open Achievements UI. Not logged in.");
            if (GameSharing::errorHandler != nullptr) {
                GameSharing::errorHandler();
            }
        }
    } else {
        GKGameCenterViewController* gkController = [[GKGameCenterViewController alloc] init];

        GameCenterDelegate *gameCenterDelegate = [GameCenterDelegate getInstance];
        gkController.gameCenterDelegate = gameCenterDelegate;
        
        [gameCenterDelegate.viewController presentViewController:gkController animated:YES completion:^{}];
    }
}

void GameSharing::submitScoreToLeaderboard(int score, int lId){
    if(numberOfLeaderboards >= lId){
        GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier: [NSString stringWithUTF8String:iosLeaderboardIds.at(lId).c_str()]];
        scoreReporter.value = score;
        scoreReporter.context = 0;
        
        [GKScore reportScores:@[scoreReporter] withCompletionHandler:^(NSError *error) {
            if (error != nil) {
                NSLog(@"Error at GameSharing::submitScoreToLeaderboard()");
                if (GameSharing::errorHandler != nullptr) {
                    GameSharing::errorHandler();
                }
            }
        }];
    }
}

void GameSharing::unlockAchievement(int aId){
    if(numberOfAchievements >= aId){
        GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier:
                                      [NSString stringWithUTF8String:iosAchievementIds.at(aId).c_str()]];
        if (achievement){
            achievement.percentComplete = 100;
            achievement.showsCompletionBanner = true;
            [GKAchievement reportAchievements:@[achievement] withCompletionHandler:^(NSError *error) {
                if (error != nil) {
                    NSLog(@"Error at GameSharing::unlockAchievement()");
                    if (GameSharing::errorHandler != nullptr) {
                        GameSharing::errorHandler();
                    }
                }
            }];
        }
    }
}

void GameSharing::startScoreRequest(int leaderboardID)
{
    if(iosLeaderboardIds.size() >= leaderboardID){
        if (![GKLocalPlayer localPlayer].isAuthenticated) {
            signInPlayer();
        }else{
            GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
            leaderboardRequest.identifier = [NSString stringWithUTF8String:iosLeaderboardIds.at(leaderboardID).c_str()];
            if (leaderboardRequest != nil) {
                [leaderboardRequest loadScoresWithCompletionHandler:^(NSArray *scores, NSError *error){
                    if (error != nil) {
                        NSLog(@"The score could not be requested.");
                        GameSharing::localPlayerScore = -1;
                    }
                    else{
                        auto highestScore = leaderboardRequest.localPlayerScore;
                        GameSharing::localPlayerScore = int(highestScore.value);
                        GameSharing::requestIsBeingProcessed = false;
                        if(GameSharing::requestCallback)
                        {
                            NSLog(@"Calling Callback");
                            GameSharing::requestCallback();
                        }
                    }
                }];
            }
        }
    }
}

bool GameSharing::signInPlayer(){
    GKLocalPlayer *player = [GKLocalPlayer localPlayer];
    bool signedIn=false;
    player.authenticateHandler = ^(UIViewController *viewController, NSError *error){
        if (viewController != nil)
        {
            if (viewController != nil && player.authenticated == false)
            {
                [[GameCenterDelegate getInstance].viewController presentViewController:viewController animated:YES completion:^{}];
            }
        }
    };
    if (player.isAuthenticated) {
        signedIn = true;
    }
    return  signedIn;
}
