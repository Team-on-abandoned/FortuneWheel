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

	void StartGame();

private:
	SlotsController slotsController;
	SlotMachineHandle slotMachineHandle;
	TokenInfo tokenInfo;
	WinEffects winEffects;
};

