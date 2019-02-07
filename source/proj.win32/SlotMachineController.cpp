#include "SlotMachineController.h"
#include "Settings.h"

USING_NS_CC;


SlotMachineController::SlotMachineController() {
}


SlotMachineController::~SlotMachineController() {
}

void SlotMachineController::StartGame(cocos2d::Scene *scene) {
	this->scene = scene;

	CreateStaticSprites();
}

void SlotMachineController::CreateStaticSprites() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SlotMachineController::MenuCloseCallback, this)
	);

	if (closeItem != nullptr && closeItem->getContentSize().width > 0 && closeItem->getContentSize().height > 0) {
		closeItem->setPosition(Vec2(
			visibleSize.width - closeItem->getContentSize().width / 2,
			closeItem->getContentSize().height / 2
		));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	scene->addChild(menu, Settings::z_btn_exit);

	auto tmpSprite = Sprite::create("Art\\SlotMachine.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setAnchorPoint(Vec2(0.5, 0.5));
		tmpSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		center = tmpSprite->getPosition();
		scene->addChild(tmpSprite, Settings::z_sprite_slotMachine);
	}

	/*winLabel = Label::createWithTTF("You win!", "fonts/Marker Felt.ttf", 90);
	if (winLabel != nullptr) {
		winLabel->enableShadow();
		winLabel->setPosition(spriteMachine->getPosition());
		winLabel->setOpacity(0);
		scene->addChild(winLabel, 15);
	}

	fireworks[0] = ParticleFireworks::create();
	fireworks[0]->setPosition(winLabel->getPosition() - Vec2(winLabel->getContentSize().width / 2 + 10, 0));
	scene->addChild(fireworks[0], 16);
	fireworks[0]->stop();
	fireworks[1] = ParticleFireworks::create();
	fireworks[1]->setPosition(winLabel->getPosition() + Vec2(winLabel->getContentSize().width / 2 + 10, 0));
	scene->addChild(fireworks[1], 16);
	fireworks[1]->stop();*/

	tmpSprite = Sprite::create("Art\\SlotMachineForToken.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setAnchorPoint(Vec2(0.5, 0.5));
		tmpSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		scene->addChild(tmpSprite, Settings::z_sprite_slotMachine);
	}

	tmpSprite = Sprite::create("Art\\SlotMachineEmpty.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setAnchorPoint(Vec2(0.5, 0.5));
		tmpSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		scene->addChild(tmpSprite, Settings::z_sprite_slotMachineEmpty);
	}

	tmpSprite = Sprite::create("Art\\arrow.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setPosition(GetPosRelativeToCenter(-403, -11));
		scene->addChild(tmpSprite, Settings::z_sprite_arrow);
	}

	/*for (char i = 0; i < 3; ++i) {
		tmpSprite = Sprite::create("Art\\SlotBG.png");
		if (tmpSprite != nullptr) {
			tmpSprite->setPosition(spriteMachine->getPosition() + slotPos[i]);
			scene->addChild(tmpSprite, 1);
		}

		slotFrames[i][0] = Sprite::create("Art\\Frame.png");
		slotFrames[i][1] = Sprite::create("Art\\Frame.png");
		for (char j = 0; j < 2; ++j) {
			if (slotFrames[i][j] != nullptr) {
				slotFrames[i][j]->setPosition(spriteMachine->getPosition() + slotPos[i]);
				slotFrames[i][j]->setPositionY(slotFrames[i][j]->getPositionY() + j * tmpSprite->getContentSize().height);
				scene->addChild(slotFrames[i][j], 2);
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
				scene->addChild(slotSprites[i][j], 3);
			}
		}
	}*/

	tmpSprite = Sprite::create("Art\\back.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setPosition(Vec2::ZERO);
		tmpSprite->setAnchorPoint(Vec2::ZERO);
		scene->addChild(tmpSprite, 4);
	}

	/*handleUp = Sprite::create("Art\\knob1.png");
	if (handleUp != nullptr) {
		handleUp->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 115));
		scene->addChild(handleUp, 6);
	}

	handleUpActive = Sprite::create("Art\\KnobGlowHL.png");
	if (handleUpActive != nullptr) {
		handleUpActive->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 115));
		handleUpActive->setOpacity(0);
		scene->addChild(handleUpActive, 7);
	}

	handleDown = Sprite::create("Art\\KnobDown.png");
	if (handleDown != nullptr) {
		handleDown->setPosition(Vec2(spriteMachine->getPositionX() + 420, spriteMachine->getPositionY() + 12));
		handleDown->setContentSize(handleDown->getContentSize());
		handleDown->setOpacity(0);
		scene->addChild(handleDown, 8);
	}

	if (handleUpActive != nullptr && handleUp != nullptr && handleDown != nullptr) {
		auto listener = EventListenerMouse::create();
		listener->onMouseDown = CC_CALLBACK_1(Save::HandleMouseDown, this);
		listener->onMouseUp = CC_CALLBACK_1(Save::HandleMouseUp, this);
		listener->onMouseMove = CC_CALLBACK_1(Save::GlowHandle, this);

		_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
	}

	token = Sprite::create("Art\\token.png");
	if (token != nullptr) {
		token->setPosition(Vec2(spriteMachine->getPosition()) + Vec2(580, -170));
		tokenStartPos = token->getPosition();
		scene->addChild(token, 10);
	}

	insertToken = Sprite::create("Art\\insertToken.png");
	if (insertToken != nullptr) {
		insertToken->setPosition(Vec2(spriteMachine->getPosition()) + Vec2(290, -13));
		insertToken->setOpacity(0);
		tokenInsertStartPos = insertToken->getPosition();
		tokenInsertEndPos = tokenInsertStartPos - Vec2(50, 0);
		scene->addChild(insertToken, 11);
	}*/
}

Vec2 SlotMachineController::GetPosRelativeToCenter(int x, int y) {
	return center + Vec2(x, y);
}

void SlotMachineController::MenuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}
