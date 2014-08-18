GameSharing
===========

GameSharing is C++ bridge to the Java Google Play Games Services SDK for cocos2d-X.
You can use this features at the moment:
* Submit scores to Leaderboards
* Open the Leaderboards UI
* Unlock Achievements

Requirements
===========

You project must use cocos2d-x 3.2 or higher and you must already have Google Play Services set up for your project.

How to use GameSharing
=====================

To use Game Sharing you only have to add the class body  and the imports from AppActvity to your AppActvity.java
class, after that copy the other .java files into your project and replace all your.app.id keywords with your app ID.
Once you did that, set MainActivity to the main activity in your AndroidMainfest.xml file and add AppActvity and NoGPGAppActvity
to the list of Activitys. Then copy the C++/GameSharing.cpp and C++/GameSharing.h file into your project and you are good to go.
For more information please take a look at the wiki.

Is my project still compatible with other operating system if I use GameSharing
===============================================================================

Yes it is. The GameSharing class only compiles the Google Play Games relevant parts, if you compile for android.
On other operating system all methods just have no effect at all, but won't produce any compiler errors.
