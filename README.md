GameSharing
===========

GameSharing is C++ bridge to the Java Google Play Games Services SDK for cocos2d-X.
You can use this features at the moment:
* Submit scores to Leaderboards
* Open the Leaderboards UI
* Unlock Achivements

Requirements
===========

You project must use cocos2d-x 3.2 or higher and you must already have set up Google Play Services for your project.

How to use GameSharing
=====================

To use Game Sharing you only have to add the class body from AppActvity to your AppActvity.java
class. Then copy the GameSharing.cpp and GameSharing.h files to your project and you are good to go.
For more information please take a look at the wiki.

Is my project still compatible with other operation systems if I use GameSharing
===============================================================================

Yes it is. The GameSharing class only compiles the Google Play Games relevant parts, if you compile for android.
On other operating system all methods just have no effect at all, but won't produce any compiler errors.
