//
//  HomeScene.h
//  SimpleGame
//
//  Created by sakura on 2014/02/19.
//
//

#ifndef __SimpleGame__HomeScene__
#define __SimpleGame__HomeScene__


#include "cocos2d.h"

class HomeScene : public cocos2d::CCLayerColor
{
public:
	HomeScene();
	~HomeScene();

	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void menuCloseCallback(cocos2d::CCObject* pSender);

	CREATE_FUNC(HomeScene);


private:
	void tapStartButton();
};

#endif /* defined(__SimpleGame__HomeScene__) */
