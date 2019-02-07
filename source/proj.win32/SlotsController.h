#pragma once
#include "cocos2d.h"
#include <vector>
#include "Slot.h"

class SlotsController {
public:
	SlotsController();
	~SlotsController();

	//Загружає спрайти всіх для слотів
	void AddSprite(cocos2d::Sprite *sprite);
	//Створює слот на позиції slotPos. Викликатии лише після всіх викликів AddSprite().
	void AddSlot(cocos2d::Scene *scene, cocos2d::Vec2 slotPos);

	//Робить кожний 2 виклик Roll() виграшним
	void EnableDebugMode(){ isInDebugMode = true; }
	void DisableDebugMode(){ isInDebugMode = false; }

	void Roll();

	bool IsWin();

	void SetDurationForRoll(float _durationForRoll) { durationForRoll = _durationForRoll; }
	void SetMaxRotates(float _maxRotates){ maxRotates = _maxRotates;}

private:
	cocos2d::Scene *scene;
	std::vector<cocos2d::Sprite*> sprites;
	std::vector<Slot> slots;

	int rollCnt;
	float durationForRoll;
	char  maxRotates;

	bool isInDebugMode;
};
