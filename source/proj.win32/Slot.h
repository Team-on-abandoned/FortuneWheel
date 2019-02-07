#pragma once
#include "cocos2d.h"

class Slot {
public:
	Slot();
	~Slot();

private:
	cocos2d::Vec2 slotPos;
	cocos2d::Sprite *slotFrames[2];
	std::vector<cocos2d::Sprite*> sprites;
	char currentSprite;
};

