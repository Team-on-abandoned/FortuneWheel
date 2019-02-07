#pragma once
#include "cocos2d.h"

#include "SlotsController.h"
#include "SlotMachineHandle.h"
#include "TokenInfo.h"
#include "WinEffects.h"

class SlotMachineController {
public:
	SlotMachineController();
	~SlotMachineController();

	void StartGame(cocos2d::Scene *scene);

private:
	cocos2d::Scene *scene;
	cocos2d::Vec2 center;

	SlotsController slotsController;
	SlotMachineHandle slotMachineHandle;
	TokenInfo tokenInfo;
	WinEffects winEffects;

	void CreateStaticSprites();
	cocos2d::Vec2 GetPosRelativeToCenter(int x, int y);

	void MenuCloseCallback(cocos2d::Ref* pSender);
};

