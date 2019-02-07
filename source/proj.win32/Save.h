#pragma once
#include "cocos2d.h"

class Save : public cocos2d::Scene {
	cocos2d::EventListenerMouse* mouseListener;
	bool downMouseOnHandle, handleIsDown, animationPlaying;

	cocos2d::Vec2 slotPos[3], tokenStartPos, tokenInsertStartPos, tokenInsertEndPos;
	cocos2d::Sprite *slotSprites[3][5], *slotFrames[3][2], *handleUp, *handleUpActive, *handleDown, *token, *insertToken;
	cocos2d::Label *winLabel;
	cocos2d::ParticleFireworks *fireworks[2];
	char currentSlot[3];

	void CreateSprites();
	void PlayCoinAnimation();
	void RollSlotRec(char slotNum, float duration, char rotates);
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(Save);
	virtual bool init();

	void MenuCloseCallback(cocos2d::Ref* pSender);

	void GlowHandle(cocos2d::Event *event);
	void HandleMouseDown(cocos2d::Event *event);
	void HandleMouseUp(cocos2d::Event *event);

	void RollSlots();
	void RollSlot(char slotNum, float duration, char rotates);

	void CheckWin();
};
