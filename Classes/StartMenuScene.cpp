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
#include "SimpleAudioEngine.h"
#include "BrawlStarsMenu.h"

USING_NS_CC;

Scene* StartMenuScene::createScene()
{  
    auto layer = BrawlStarsMenu::createLayer();
    auto scene= StartMenuScene::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool StartMenuScene::init()
{


    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(StartMenuScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

   
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    auto exitBtnPic = cocos2d::MenuItemImage::create("Normal_Button.png",
        "Pressed_Button.png",
        CC_CALLBACK_1(StartMenuScene::menuCloseCallback, this));
    if (exitBtnPic == nullptr ||
        exitBtnPic->getContentSize().width <= 0 ||
        exitBtnPic->getContentSize().height <= 0)
    {
        //problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

    }
    else
    {
        float x = origin.x + visibleSize.width / 3;
        float y = origin.y + visibleSize.height / 2;
        exitBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
        exitBtnPic->setPosition(cocos2d::Vec2(x, y));
    }

    auto exitButton = Menu::create(exitBtnPic, nullptr);
    //这里以前错写为menu->setPosition(Vec2...)导致按钮未显示
    exitButton->setPosition(Vec2::ZERO);
    this->addChild(exitButton, 0);

    
    auto layer1 = LayerColor::create(Color4B(255, 0, 0, 255), 100, 100);
    layer1->setPosition(Vec2(200, 200));
    this->addChild(layer1, 0);

    auto layer2 = LayerColor::create(Color4B(255, 125, 0, 255), 100, 100);
    layer2->setPosition(Vec2(150, 150));
    this->addChild(layer2);

    auto layer3 = LayerColor::create(Color4B(255, 200, 0, 255), 100, 100);
    layer3->setPosition(Vec2(100, 100));
    this->addChild(layer3);
    

    
    return true;
}


void StartMenuScene::menuCloseCallback(Ref* pSender)
{
   
    Director::getInstance()->end();

}
