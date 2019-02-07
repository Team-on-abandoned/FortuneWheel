#pragma once
#include "cocos2d.h"

class Slot {
public:
	Slot(cocos2d::Scene *scene, cocos2d::Vec2 slotPos, std::vector<cocos2d::Sprite*> sprites);
	~Slot();

	char GetCurrentSprite() { return currentSprite; }
	void Roll(float durationForAll, char rotates);

private:
	cocos2d::Scene *scene;
	cocos2d::Vec2 slotPos;
	cocos2d::Sprite *slotFrames[2];
	std::vector<cocos2d::Sprite*> sprites;
	char currentSprite;

	void RecRoll(float durationForRotate, char rotates);
};

