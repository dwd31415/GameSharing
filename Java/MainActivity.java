/*


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


Created by Adrian Dawid

*/
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

public class MainActivity extends Activity{
    public static boolean exiting = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if(!exiting)
        {
        int resultCode = GooglePlayServicesUtil.isGooglePlayServicesAvailable(getApplicationContext());
        if (resultCode == ConnectionResult.SUCCESS){
            Intent intent = new Intent(this, AppActivity.class);
            AppActivity.gpgAvailable = true;
            startActivity(intent);
        }
        else{
            Intent intent = new Intent(this, NoGPGAppActivity.class);
            AppActivity.gpgAvailable = false;
            startActivity(intent);
        }
        }
        else{
            Intent intent = new Intent(Intent.ACTION_MAIN);
            intent.addCategory(Intent.CATEGORY_HOME);
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(intent);
        }
    }
    
    @Override
    public void onStop() {
        super.onStop();
        if(exiting)
        {
            android.os.Process.killProcess(android.os.Process.myPid());
        }
    }
}
