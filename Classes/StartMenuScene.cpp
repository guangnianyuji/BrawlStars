/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "StartMenuScene.h"
#include "AudioEngine.h"
#include "BrawlStarsMenu.h"

USING_NS_CC;

Scene* StartMenuScene::createScene()
{  
    auto layer = BrawlStarsMenu::createLayer();
    layer->setName("bsmenuLayer");

    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();


    float x = origin.x - visibleSize.width ;
    float y = origin.y - visibleSize.height ;

    layer->setPosition(x, y);


    auto scene= StartMenuScene::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void StartMenuScene::drawBackGround()
{
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    this->bgSprite = cocos2d::Sprite::create("background.jpg");
    if (bgSprite == nullptr)
    {
      
    }
    else
    {
        bgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(bgSprite, 0);
    }
}

void StartMenuScene::initMenuButton()
{
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto menuBtnPic = cocos2d::MenuItemImage::create("Normal_menuButton.png",
        "Pressed_menuButton.png",
        CC_CALLBACK_1(StartMenuScene::menuCallback, this));
    if (menuBtnPic == nullptr ||
        menuBtnPic->getContentSize().width <= 0 ||
        menuBtnPic->getContentSize().height <= 0)
    {
        //problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

    }
    else
    {
        float x = origin.x;
        float y = origin.y+ visibleSize.height / 1.2;
        menuBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
        menuBtnPic->setPosition(cocos2d::Vec2(x, y));
    }

    this->menuButton = Menu::create(menuBtnPic, nullptr);
    this->addChild(menuButton, 5);
    menuButton->setPosition(Vec2::ZERO);

}

void StartMenuScene::bgplayMusic()
{
    int bgMusicID = experimental::AudioEngine::play2d("bgMusic.mp3");
}



bool StartMenuScene::init()
{


    if ( !Scene::init() )
    {
        return false;
    }

    drawBackGround();
    initMenuButton();
    bgplayMusic();
    return true;
}

void StartMenuScene::menuCallback(Ref* pSender)
{
    auto menuLayer = this->getChildByName("bsmenuLayer");


    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    float x = origin.x;//+ visibleSize.width / 2;
    float y = origin.y - visibleSize.height / 5;

    menuLayer->setPosition(Vec2(x, y));
}

