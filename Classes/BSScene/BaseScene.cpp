
#include "BaseScene.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* BaseScene::createScene()
{  
    auto scene= BaseScene::create();
    return scene;
}

static void problemLoading(const char* filename)
{
}

void BaseScene::drawBackGround(cocos2d::Sprite* bgSprite)
{
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    this->bgSprite = bgSprite;
    if (this->bgSprite == nullptr)
    {
      
    }
    else
    {
        this->bgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(this->bgSprite, 0);
    }
}

/* ��ÿ�������м���˵�ͼ�� */
void BaseScene::addMenu()
{
    auto layer = BrawlStarsMenu::createLayer();

    if(layer==nullptr)
    { 
    }
    else
    {
        /* ���˵��ڵ�����������֮���ȡ */
        layer->setName("bsmenuLayer");

        //layer->setAnchorPoint(Vec2(0.5, 0.5));

        //layer->setScale(0.5);

        Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

        /* Ĭ�ϲ˵������Ӵ��ڣ����°�ť��ı�λ�� */
        float x = origin.x + visibleSize.width*2;
        float y = origin.y + visibleSize.height*2;

        layer->setPosition(x, y);

        this->addChild(layer,5);
    }
}

void BaseScene::initMenuButton()
{
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto menuBtnPic = cocos2d::MenuItemImage::create("ui/Options.png",
        "ui/Options.png",
        CC_CALLBACK_1(BaseScene::menuCallback, this));
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


bool BaseScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    addMenu();
    initMenuButton();
    return true;
}

void BaseScene::menuCallback(Ref* pSender)
{
    auto menuLayer = this->getChildByName("bsmenuLayer");


    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    float x = origin.x;
    float y = origin.y - visibleSize.height / 5;

    menuLayer->setPosition(Vec2(x, y));
}

