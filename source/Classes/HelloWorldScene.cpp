#include <iostream>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using std::cout;
using std::endl;

Scene* HelloWorld::createScene() {
	return HelloWorld::create();
}

bool HelloWorld::init() {
	if (!Scene::init())
		return false;

	slotPos[0] = Vec2(-303, -11);
	slotPos[1] = Vec2(-103, -11);
	slotPos[2] = Vec2(98, -11);

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

	CreateSprites();


	return true;
}

void HelloWorld::CreateSprites() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

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

	handleUp = Sprite::create("Art\\knob1.png");
	if (handleUp != nullptr) {
		handleUp->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 115));
		addChild(handleUp, 6);
	}

	handleUpActive = Sprite::create("Art\\KnobGlowHL.png");
	if (handleUpActive != nullptr) {
		handleUpActive->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 115));
		addChild(handleUpActive, 7);
	}

	handleDown = Sprite::create("Art\\KnobDown.png");
	if (handleDown != nullptr) {
		handleDown->setPosition(Vec2(spriteMachine->getPositionX() + 428, spriteMachine->getPositionY() + 12));
		handleDown->setContentSize(handleDown->getContentSize() * 1.2);
		addChild(handleDown, 8);
	}

	token = Sprite::create("Art\\token.png");
	if (token != nullptr) {
		token->setPosition(Vec2(spriteMachine->getPosition()) + Vec2(580, -170));
		addChild(token, 10);
	}

	insertToken = Sprite::create("Art\\insertToken.png");
	if (insertToken != nullptr) {
		insertToken->setPosition(Vec2(spriteMachine->getPosition()) + Vec2(290, -13));
		addChild(insertToken, 11);
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}
