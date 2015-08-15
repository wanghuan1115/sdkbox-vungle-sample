#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "PluginVungle/PluginVungle.h"

USING_NS_CC;

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    FileUtils::getInstance()->addSearchPath("res");
    
    sdkbox::PluginVungle::init();
    sdkbox::PluginVungle::setListener(this);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    
    _btnVideo = rootNode->getChildByName<ui::Button*>("btnVideo");
    _btnVideo->addClickEventListener(CC_CALLBACK_1(HelloWorld::onPlayVideo, this));
    _btnVideo->setEnabled(false);
    
    _btnReward = rootNode->getChildByName<ui::Button*>("btnReward");
    _btnReward->addClickEventListener(CC_CALLBACK_1(HelloWorld::onPlayReward, this));
    _btnReward->setEnabled(false);
    
    _txtCoin = rootNode->getChildByName<ui::Text*>("txtCoins");
    
    auto btnClose = rootNode->getChildByName<ui::Button*>("btnClose");
    btnClose->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    return true;
}

/**
 * Button callback
 */

void HelloWorld::onPlayVideo(Ref *pSender)
{
    sdkbox::PluginVungle::show("video");
}

void HelloWorld::onPlayReward(Ref* sender)
{
    sdkbox::PluginVungle::show("reward");
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onVungleCacheAvailable()
{
    CCLOG("Video loaded");
    _btnVideo->setEnabled(true);
    _btnReward->setEnabled(true);
}


void HelloWorld::onVungleStarted()
{
    CCLOG("Video started");
}

void HelloWorld::onVungleFinished()
{
    CCLOG("Video finished");
}

void HelloWorld::onVungleAdViewed(bool isComplete)
{
    CCLOG("Video viewed");
    if (isComplete) {
        _coin ++;
        _txtCoin->setString(to_string(_coin));
    }
}

