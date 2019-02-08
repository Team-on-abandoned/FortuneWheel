#pragma once
#include "cocos2d.h"

class SlotMachineHandle {
public:
	SlotMachineHandle();
	~SlotMachineHandle();

	void Init(cocos2d::Scene *scene, cocos2d::Vec2 handlePos, cocos2d::Vec2 handleDownPos);

private:
	cocos2d::EventListenerMouse* mouseListener;

	cocos2d::Sprite *handleUp, *handleUpActive, *handleDown;
	bool downMouseOnHandle, isHandleDown;

	void GlowHandle(cocos2d::Event *event);
	void HandleMouseDown(cocos2d::Event *event);
	void HandleMouseUp(cocos2d::Event *event);
};

