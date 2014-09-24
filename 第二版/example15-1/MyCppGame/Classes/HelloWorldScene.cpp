#include "HelloWorldScene.h"

USING_NS_CC;


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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);


    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    auto playSp = Sprite::create("general_right.png");
    playSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(playSp);
    /*auto backgroundButton = Scale9Sprite::create("general_right.png");
    auto titleButton = LabelTTF::create("", "Marker Felt", 30);
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    button->setAdjustBackgroundImage(false); 
    this->addChild(button);*/
    GLchar * pszFragSource =
    "#ifdef GL_ES \n \
    precision mediump float; \n \
    #endif \n \
    uniform sampler2D u_texture; \n \
    varying vec2 v_texCoord; \n \
    varying vec4 v_fragmentColor; \n \
    void main(void) \n \
    { \n \
    // Convert to greyscale using NTSC weightings \n \
    float grey = dot(texture2D(u_texture, v_texCoord).rgb, vec3(0.299, 0.587, 0.114)); \n \
    gl_FragColor = vec4(grey, grey, grey, 1.0); \n \
    }";
    GLProgram* greyShader = new GLProgram();
    greyShader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
    greyShader->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    greyShader->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    greyShader->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    greyShader->link();
    greyShader->updateUniforms();
    //backgroundButton->setShaderProgram(greyShader);
    sprite->setShaderProgram(greyShader);
    playSp->setShaderProgram(greyShader);
    /*Array * children = button->getChildren();
    for(int i = 0;i < children->count();i ++){
        ((Node *)children->getObjectAtIndex(i))->setShaderProgram(greyShader);
    }*/
    
    greyShader->release();
    
    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
