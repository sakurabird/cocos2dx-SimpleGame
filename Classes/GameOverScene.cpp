/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2010      Ray Wenderlich
 
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

#include "GameOverScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameOverScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

GameOverScene::~GameOverScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}


bool GameOverLayer::init()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	bool bRet = false;
	do
	{
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) );

		this->_label = CCLabelTTF::create("","Artial", 30);
        CC_BREAK_IF(! _label);
		_label->retain();
		_label->setColor( ccc3(0, 0, 0) );
		_label->setPosition( ccp(winSize.width/2, winSize.height/2) );
		this->addChild(_label);

		this->_label2 = CCLabelTTF::create("","Artial", 20);
        CC_BREAK_IF(! _label2);
		_label2->retain();
		_label2->setColor( ccc3(0, 0, 0) );
		_label2->setPosition( ccp(winSize.width/2, winSize.height * 0.7) );
		this->addChild(_label2);


        CCLabelTTF* restartLabel = CCLabelTTF::create("Restart!", "Arial", 42.0);

        CC_BREAK_IF(! restartLabel);
        restartLabel->setColor(ccc3(255,192,203));
        CCMenuItemLabel* restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(GameOverLayer::gameOverDone));
        restartItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));

        CCMenu* menu = CCMenu::create(restartItem, NULL);
        menu->setPosition(CCPointZero);
        this->addChild(menu);



//        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                                              "CloseNormal.png",
//                                                              "CloseSelected.png",
//                                                              this,
//                                                              menu_selector(GameOverLayer::menuCloseCallback));


        CCSprite* closeNormal = CCSprite::createWithSpriteFrameName("CloseNormal.png");
        CCSprite* closeSelected = CCSprite::createWithSpriteFrameName("CloseSelected.png");
        CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(closeNormal,
                                                                closeSelected,
                                                                this,
                                                                menu_selector(GameOverLayer::menuCloseCallback));

        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2,origin.y + pCloseItem->getContentSize().height/2));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);

        this->addChild(pMenu, 1);


        bRet = true;
	} while (0);

	return bRet;
}

void GameOverLayer::setResult(int score)
{
    if (score >= 5) {
        _label->setString("あなたの勝ちヽ(=´▽`=)ﾉ");
    } else {
        _label->setString("あなたの負け(´・ω・`)");
    }

    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    const char* highScoreKey = "highscore";

    int highScore = userDefault->getIntegerForKey(highScoreKey, 0);
    if (score != 0)
    {
        if (score > highScore)
        {
            // ハイスコアを更新する
            highScore = score;
            userDefault->setIntegerForKey(highScoreKey, highScore);
            userDefault->flush();
        }
    }

    CCString* highScoreString = CCString::createWithFormat("スコア：%d　ハイスコア：%d", score,highScore);
	_label2->setString(highScoreString->getCString());

}

void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene( HelloWorld::scene() );
}

void GameOverLayer::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    CCDirector::sharedDirector()->end();
#endif
}

GameOverLayer::~GameOverLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
	if (_label2)
	{
		_label2->release();
		_label2 = NULL;
	}
}
