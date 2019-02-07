#pragma once
#include "cocos2d.h"

class SlotMachineHandle {
public:
	SlotMachineHandle();
	~SlotMachineHandle();

	void (*OnHandleDown)();

private:
	cocos2d::EventListenerMouse* mouseListener;

	cocos2d::Sprite *handleUp, *handleUpActive, *handleDown;
	bool downMouseOnHandle, handleIsDown;

	void GlowHandle(cocos2d::Event *event);
	void HandleMouseDown(cocos2d::Event *event);
	void HandleMouseUp(cocos2d::Event *event);
};

