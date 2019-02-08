#pragma once
#include "cocos2d.h"
#include "SlotsController.h"
#include "TokenInfo.h"
#include "WinEffects.h"

class SlotMachineHandle {
public:
	SlotMachineHandle();
	~SlotMachineHandle();

	void Init(cocos2d::Scene *scene, cocos2d::Vec2 handlePos, cocos2d::Vec2 handleDownPos);
	void Link(SlotsController *slotsController, TokenInfo *tokenInfo, WinEffects *winEffects);

	void HandleDown();
	void HandleUp();
private:
	cocos2d::Scene * scene;
	cocos2d::EventListenerMouse* mouseListener;

	SlotsController *slotsController;
	TokenInfo *tokenInfo;
	WinEffects *winEffects;

	cocos2d::Sprite *handleUp, *handleUpActive, *handleDown;
	bool downMouseOnHandle, isHandleDown;


	void GlowHandle(cocos2d::Event *event);
	void HandleMouseDown(cocos2d::Event *event);
	void HandleMouseUp(cocos2d::Event *event);
};

