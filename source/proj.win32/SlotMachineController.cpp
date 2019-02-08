#include "SlotMachineController.h"
#include "Settings.h"

USING_NS_CC;


SlotMachineController::SlotMachineController() {
	slotsController.SetDurationForRoll(2);
	slotsController.SetMaxRotates(25);
	slotsController.EnableDebugMode();
}


SlotMachineController::~SlotMachineController() {
}

void SlotMachineController::StartGame(cocos2d::Scene *scene) {
	this->scene = scene;

	CreateStaticSprites();

	slotsController.AddSprite(Sprite::create("Art\\pw_slot.png"));
	slotsController.AddSprite(Sprite::create("Art\\slot_feather.png"));
	slotsController.AddSprite(Sprite::create("Art\\slot_gold.png"));
	slotsController.AddSprite(Sprite::create("Art\\slot_seven.png"));
	slotsController.AddSprite(Sprite::create("Art\\slot_tickets.png"));

	slotsController.AddSlot(scene, GetPosRelativeToCenter(-303, -11));
	slotsController.AddSlot(scene, GetPosRelativeToCenter(-103, -11));
	slotsController.AddSlot(scene, GetPosRelativeToCenter(98, -11));

	winEffects.Init(scene, center);
	tokenInfo.Init(scene, 
		GetPosRelativeToCenter(580, -170), 
		GetPosRelativeToCenter(285, -13),
		GetPosRelativeToCenter(290, -13),
		GetPosRelativeToCenter(240, -13)
	);
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

	tmpSprite = Sprite::create("Art\\SlotMachineForToken.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setAnchorPoint(Vec2(0.5, 0.5));
		tmpSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		scene->addChild(tmpSprite, Settings::z_sprite_slotMachineForToken);
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


	tmpSprite = Sprite::create("Art\\back.png");
	if (tmpSprite != nullptr) {
		tmpSprite->setPosition(Vec2::ZERO);
		tmpSprite->setAnchorPoint(Vec2::ZERO);
		scene->addChild(tmpSprite, Settings::z_sprite_Background);
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
	*/
}

Vec2 SlotMachineController::GetPosRelativeToCenter(int x, int y) {
	return center + Vec2(x, y);
}

void SlotMachineController::MenuCloseCallback(Ref* pSender) {
	//Director::getInstance()->end();

	if (!slotsController.GetIsAnimationPlaying()) {
		if (slotsController.IsWin())
			winEffects.Enable();
		else
			winEffects.Disable();

		slotsController.Roll();
		tokenInfo.PlayAnimation();
	}
}
