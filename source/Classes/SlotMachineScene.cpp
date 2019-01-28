#include <iostream>
#include "SlotMachineScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using std::cout;
using std::endl;

Scene* SlotMachineScene::createScene() {
	return SlotMachineScene::create();
}

bool SlotMachineScene::init() {
	if (!Scene::init())
		return false;

	handleIsDown = animationPlaying = downMouseOnHandle = false;
	slotPos[0] = Vec2(-303, -11);
	slotPos[1] = Vec2(-103, -11);
	slotPos[2] = Vec2(98, -11);
	currentSlot[0] = currentSlot[1] = currentSlot[2] = 0;

	/*
	auto label = Label::createWithTTF("You win!", "fonts/Marker Felt.ttf", 24);
	if (label != nullptr) {
		label->setPosition(Vec2(visibleSize.width / 2,
			visibleSize.height - label->getContentSize().height));
		addChild(label, 1);
	}
		auto emitter = ParticleFireworks::create();
	addChild(emitter, 10);

	*/

	mouseListener = EventListenerMouse::create();

	CreateSprites();

	return true;
}

void SlotMachineScene::CreateSprites() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SlotMachineScene::MenuCloseCallback, this));

	if (closeItem != nullptr &&
		closeItem->getContentSize().width > 0 &&
		closeItem->getContentSize().height > 0
		) {
		closeItem->setPosition(Vec2(
			visibleSize.width - closeItem->getContentSize().width / 2,
			closeItem->getContentSize().height / 2
		));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);

	auto spriteMachine = Sprite::create("Art\\SlotMachine.png");
	if (spriteMachine != nullptr) {
		spriteMachine->setAnchorPoint(Vec2(0.5, 0.5));
		spriteMachine->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		addChild(spriteMachine, 0);
	}

	spriteMachine = Sprite::create("Art\\SlotMachineForToken.png");
	if (spriteMachine != nullptr) {
		spriteMachine->setAnchorPoint(Vec2(0.5, 0.5));
		spriteMachine->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		addChild(spriteMachine, 12);
	}

	spriteMachine = Sprite::create("Art\\SlotMachineEmpty.png");
	if (spriteMachine != nullptr) {
		spriteMachine->setAnchorPoint(Vec2(0.5, 0.5));
		spriteMachine->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		addChild(spriteMachine, 5);
	}

	auto tmpSprite = Sprite::create("Art\\arrow.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setPosition(Vec2(spriteMachine->getPositionX() - 403, spriteMachine->getPositionY() - 11));
		addChild(tmpSprite, 6);
	}

	for (char i = 0; i < 3; ++i) {
		tmpSprite = Sprite::create("Art\\SlotBG.png");
		if (tmpSprite != nullptr) {
			tmpSprite->setPosition(spriteMachine->getPosition() + slotPos[i]);
			addChild(tmpSprite, 1);
		}

		slotFrames[i][0] = Sprite::create("Art\\Frame.png");
		slotFrames[i][1] = Sprite::create("Art\\Frame.png");
		for (char j = 0; j < 2; ++j) {
			if (slotFrames[i][j] != nullptr) {
				slotFrames[i][j]->setPosition(spriteMachine->getPosition() + slotPos[i]);
				slotFrames[i][j]->setPositionY(slotFrames[i][j]->getPositionY() + j * tmpSprite->getContentSize().height);
				addChild(slotFrames[i][j], 2);
			}
		}


		slotSprites[i][0] = Sprite::create("Art\\pw_slot.png");
		slotSprites[i][1] = Sprite::create("Art\\slot_feather.png");
		slotSprites[i][2] = Sprite::create("Art\\slot_gold.png");
		slotSprites[i][3] = Sprite::create("Art\\slot_seven.png");
		slotSprites[i][4] = Sprite::create("Art\\slot_tickets.png");
		for (char j = 0; j < 5; ++j) {
			if (slotSprites[i][j] != nullptr) {
				slotSprites[i][j]->setPosition(spriteMachine->getPosition() + slotPos[i]);
				slotSprites[i][j]->setPositionY(slotSprites[i][j]->getPositionY() + j * tmpSprite->getContentSize().height);
				addChild(slotSprites[i][j], 3);
			}
		}
	}

	tmpSprite = Sprite::create("Art\\back.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setPosition(Vec2::ZERO);
		tmpSprite->setAnchorPoint(Vec2::ZERO);
		addChild(tmpSprite, 4);
	}

	handleUp = Sprite::create("Art\\knob1.png");
	if (handleUp != nullptr) {
		handleUp->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 115));
		addChild(handleUp, 6);
	}

	handleUpActive = Sprite::create("Art\\KnobGlowHL.png");
	if (handleUpActive != nullptr) {
		handleUpActive->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 115));
		handleUpActive->setOpacity(0);
		addChild(handleUpActive, 7);
	}

	handleDown = Sprite::create("Art\\KnobDown.png");
	if (handleDown != nullptr) {
		handleDown->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 12));
		handleDown->setContentSize(handleDown->getContentSize());
		handleDown->setOpacity(0);
		addChild(handleDown, 8);
	}

	if (handleUpActive != nullptr && handleUp != nullptr && handleDown != nullptr) {
		auto listener = EventListenerMouse::create();
		listener->onMouseDown = CC_CALLBACK_1(SlotMachineScene::HandleMouseDown, this);
		listener->onMouseUp = CC_CALLBACK_1(SlotMachineScene::HandleMouseUp, this);
		listener->onMouseMove = CC_CALLBACK_1(SlotMachineScene::GlowHandle, this);

		_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
	}

	token = Sprite::create("Art\\token.png");
	if (token != nullptr) {
		token->setPosition(Vec2(spriteMachine->getPosition()) + Vec2(580, -170));
		tokenStartPos = token->getPosition();
		addChild(token, 10);
	}

	insertToken = Sprite::create("Art\\insertToken.png");
	if (insertToken != nullptr) {
		insertToken->setPosition(Vec2(spriteMachine->getPosition()) + Vec2(290, -13));
		insertToken->setOpacity(0);
		tokenInsertStartPos = insertToken->getPosition();
		tokenInsertEndPos = tokenInsertStartPos - Vec2(50, 0);
		addChild(insertToken, 11);
	}
}

void SlotMachineScene::MenuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}

void SlotMachineScene::GlowHandle(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (!handleIsDown && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		handleUpActive->setOpacity(255);
	}
	else {
		handleUpActive->setOpacity(0);
	}
}

void SlotMachineScene::HandleMouseDown(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2))
		downMouseOnHandle = true;
}

void SlotMachineScene::HandleMouseUp(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (downMouseOnHandle && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		downMouseOnHandle = false;

		if (!animationPlaying) {
			animationPlaying = handleIsDown = true;
			handleUp->setOpacity(0);
			handleUpActive->setOpacity(0);
			handleDown->setOpacity(255);

			PlayCoinAnimation();
		}
	}

}

void SlotMachineScene::PlayCoinAnimation() {
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

void SlotMachineScene::RollSlots() {
	int duration = 2;

	RollSlot(0, duration, random() % 25 + 1);
	RollSlot(1, duration, random() % 20 + 1);
	RollSlot(2, duration, random() % 10 + 1);

	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(duration);
	cocos2d::CallFunc* stopAnim = cocos2d::CallFunc::create([this]() {
		animationPlaying = false;
	});
	cocos2d::CallFunc* checkWin = cocos2d::CallFunc::create([this]() {
		animationPlaying = false;
	});
	runAction(cocos2d::Sequence::create(delay, stopAnim, checkWin, nullptr));
}

void SlotMachineScene::RollSlot(char slotNum, float duration, char rotates) {
	RollSlotRec(slotNum, duration / rotates, rotates);
}

void SlotMachineScene::RollSlotRec(char slotNum, float duration, char rotates) {
	for (char i = 0; i < 5; ++i)
		slotSprites[slotNum][i]->runAction(MoveBy::create(duration, Vec2(0, -(**slotFrames)->getContentSize().height)));

	auto move = MoveBy::create(duration, Vec2(0, -(**slotFrames)->getContentSize().height));
	auto changeSlotBack = CallFunc::create([this, slotNum]() {
		auto tmp = slotFrames[slotNum][0]->getPosition();
		slotFrames[slotNum][0]->setPosition(slotFrames[slotNum][1]->getPosition());
		slotFrames[slotNum][1]->setPosition(slotFrames[slotNum][0]->getPosition());

	});

	slotFrames[slotNum][0]->runAction(Sequence::create(move, changeSlotBack, nullptr));

	cocos2d::CallFunc* changeSlotsFigure = cocos2d::CallFunc::create([this, slotNum]() {
		char place = currentSlot[slotNum] - 1;
		if (place == -1)
			place = 4;

		slotSprites[slotNum][currentSlot[slotNum]]->
			setPosition(
				slotSprites[slotNum][place]->getPosition() +
				Vec2(0, (**slotFrames)->getContentSize().height)
			);

		if (++currentSlot[slotNum] == 5)
			currentSlot[slotNum] = 0;
	});

	cocos2d::CallFunc* nextRoll = cocos2d::CallFunc::create([this, slotNum, duration, rotates]() {
		if(rotates != 1)
			RollSlotRec(slotNum, duration, rotates - 1);
	});

	runAction(Sequence::create(DelayTime::create(duration), changeSlotsFigure, nextRoll,  nullptr));
}