#include "AppDelegate.h"
#include "GameMainMenu.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    Size winsize = director->getVisibleSize();
    double ratio = winsize.width / winsize.height;
   
    if(ratio >= 1.775){
        glview->setDesignResolutionSize(1136,640,ResolutionPolicy::SHOW_ALL);
        
    }else if(ratio > 1.5){
        glview->setDesignResolutionSize(640*ratio,640,ResolutionPolicy::SHOW_ALL);
        
    }else{
        glview->setDesignResolutionSize(960,640,ResolutionPolicy::SHOW_ALL);
    }
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameMainMenu::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
