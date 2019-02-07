#include <iostream>
#include "Save.h"

USING_NS_CC;
using std::cout;
using std::endl;

Scene* Save::createScene() {
	return Save::create();
}

bool Save::init() {
	if (!Scene::init())
		return false;

	handleIsDown = animationPlaying = downMouseOnHandle = false;
	slotPos[0] = Vec2(-303, -11);
	slotPos[1] = Vec2(-103, -11);
	slotPos[2] = Vec2(98, -11);
	currentSlot[0] = currentSlot[1] = currentSlot[2] = 0;

	mouseListener = EventListenerMouse::create();

	return true;
}


void Save::GlowHandle(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (!handleIsDown && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		handleUpActive->setOpacity(255);
	}
	else {
		handleUpActive->setOpacity(0);
	}
}

void Save::HandleMouseDown(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2))
		downMouseOnHandle = true;
}

void Save::HandleMouseUp(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (downMouseOnHandle && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		downMouseOnHandle = false;

		if (!animationPlaying) {
			winLabel->setOpacity(0);
			fireworks[0]->stop();
			fireworks[1]->stop();

			animationPlaying = handleIsDown = true;
			handleUp->setOpacity(0);
			handleUpActive->setOpacity(0);
			handleDown->setOpacity(255);

			PlayCoinAnimation();
		}
	}

}

void Save::PlayCoinAnimation() {
	token->runAction(Sequence::create(
		Spawn::create(
			MoveTo::create(2, tokenInsertStartPos - Vec2(5, 0)),
			Sequence::create(
				DelayTime::create(1),
				CallFunc::create([this]() {
		handleUp->setOpacity(255);
		handleDown->setOpacity(0);
		handleIsDown = false;
	}),
				nullptr
		),
			nullptr
		),

		CallFunc::create([this]() {
		token->setPosition(tokenStartPos);
		insertToken->setPosition(tokenInsertStartPos);
		insertToken->setOpacity(255);

		insertToken->runAction(Sequence::create(
			MoveTo::create(2, tokenInsertEndPos),
			Spawn::create(
				FadeOut::create(2),
				CallFunc::create([this]() {
			RollSlots();
		}),
				nullptr
			),
			nullptr
			));
	}),

		nullptr
		));
}

void Save::RollSlots() {
	static int rollCnt = 2;
	int duration = 2;

	if (rollCnt++ % 2 == 0) {
		RollSlot(0, duration, random() % 25 + 1);
		RollSlot(1, duration, random() % 20 + 1);
		RollSlot(2, duration, random() % 10 + 1);
	}
	else {
		int rand = random() % 10;
		for (char i = 0; i < 3; ++i)
			RollSlot(i, duration, 4 - currentSlot[i] + rand);
	}

	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(duration + 0.5);
	cocos2d::CallFunc* stopAnim = cocos2d::CallFunc::create([this]() {
		animationPlaying = false;
	});
	cocos2d::CallFunc* checkWin = cocos2d::CallFunc::create([this]() {
		CheckWin();
	});
	runAction(cocos2d::Sequence::create(delay, stopAnim, checkWin, nullptr));
}

void Save::RollSlot(char slotNum, float duration, char rotates) {
	RollSlotRec(slotNum, duration / rotates, rotates);
}

void Save::RollSlotRec(char slotNum, float duration, char rotates) {
	if (rotates <= 0)
		return;

	for (char i = 0; i < 5; ++i)
		slotSprites[slotNum][i]->runAction(MoveBy::create(duration, Vec2(0, -(**slotFrames)->getContentSize().height)));

	auto move = MoveBy::create(duration, Vec2(0, -(**slotFrames)->getContentSize().height));
	auto changeSlotBack = CallFunc::create([this, slotNum]() {
		auto tmp = slotFrames[slotNum][0]->getPosition();
		slotFrames[slotNum][0]->setPosition(slotFrames[slotNum][1]->getPosition());
		slotFrames[slotNum][1]->setPosition(slotFrames[slotNum][0]->getPosition());

	});

	slotFrames[slotNum][0]->runAction(Sequence::create(move, changeSlotBack, nullptr));

	cocos2d::CallFunc* changeSlotsFigure = cocos2d::CallFunc::create([this, slotNum, duration, rotates]() {
		char place = currentSlot[slotNum] - 1;
		if (place == -1)
			place = 4;

		slotSprites[slotNum][currentSlot[slotNum]]->setPosition(
			slotSprites[slotNum][place]->getPosition() +
			Vec2(0, (**slotFrames)->getContentSize().height)
		);

		if (++currentSlot[slotNum] == 5)
			currentSlot[slotNum] = 0;

		RollSlotRec(slotNum, duration, rotates - 1);
	});

	cocos2d::CallFunc* nextRoll = cocos2d::CallFunc::create([this, slotNum, duration, rotates]() {
		//RollSlotRec(slotNum, duration, rotates - 1);
	});

	runAction(Sequence::create(DelayTime::create(duration), changeSlotsFigure, nextRoll, nullptr));
}

void Save::CheckWin() {
	if (currentSlot[0] == currentSlot[1] && currentSlot[1] == currentSlot[2]) {
		winLabel->setOpacity(255);
		fireworks[0]->start();
		fireworks[1]->start();
	}
}
