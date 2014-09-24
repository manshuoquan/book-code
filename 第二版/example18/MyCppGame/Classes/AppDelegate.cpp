#include "AppDelegate.h"
#include "GameMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
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
   
    director->setDisplayStats(true);

    
    director->setAnimationInterval(1.0 / 60);

    
    auto scene = GameMenu::scene();
    
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
