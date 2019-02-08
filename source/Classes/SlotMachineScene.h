#pragma once
#include "cocos2d.h"

#include "../proj.win32/SlotMachineController.h"

class SlotMachineScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(SlotMachineScene);
	virtual bool init();

private:
	SlotMachineController slotMachineController;
};
