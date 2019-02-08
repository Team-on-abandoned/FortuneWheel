#include "SlotsController.h"

USING_NS_CC;


SlotsController::SlotsController() :
	rollCnt(0),
	durationForRoll(2),
	maxRotates(25),
	isInDebugMode(false)
{

}


SlotsController::~SlotsController() {
}

void SlotsController::AddSprite(cocos2d::Sprite *sprite) {
	sprites.push_back(sprite);
}

void SlotsController::AddSlot(cocos2d::Scene *_scene, cocos2d::Vec2 slotPos) {
	scene = _scene;
	slots.push_back(Slot(scene, slotPos, sprites));
}

void SlotsController::Roll() {
	rollCnt++;
	isAnimationPlaying = true;

	if (isInDebugMode && rollCnt % 2 == 0) {
		int rand = random() % maxRotates;
		for (char i = 0; i < slots.size(); ++i)
			slots[i].Roll(durationForRoll, sprites.size() - 1 - slots[i].GetCurrentSprite() + rand);
	}
	else {
		for (char i = 0; i < slots.size(); ++i)
			slots[i].Roll(durationForRoll, random() % maxRotates + 1);
	}

	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(durationForRoll + 0.5);
	cocos2d::CallFunc* stopAnim = cocos2d::CallFunc::create([this]() {
		isAnimationPlaying = false;
	});
	scene->runAction(cocos2d::Sequence::create(delay, stopAnim, nullptr));
}

bool SlotsController::IsWin() {
	char first = slots[0].GetCurrentSprite();

	for(char i = 1; i < slots.size(); ++i)
		if(slots[i].GetCurrentSprite() != first)
			return false;

	return true;
}
