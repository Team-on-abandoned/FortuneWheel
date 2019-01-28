#pragma once
#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene {
	cocos2d::Vec2 slotPos[3];
	cocos2d::Sprite *slotSprites[3][5], *slotFrames[3][2], *handleUp, *handleUpActive, *handleDown, *token, *insertToken;

	void CreateSprites();
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(HelloWorld);
};
