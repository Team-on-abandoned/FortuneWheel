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

	slotMachineHandle.Init(scene, GetPosRelativeToCenter(420, 115), GetPosRelativeToCenter(420, 12));

	tokenInfo.Link(&slotsController);
	slotsController.Link(&winEffects);
	slotMachineHandle.Link(&slotsController, &tokenInfo, &winEffects);
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
}

Vec2 SlotMachineController::GetPosRelativeToCenter(int x, int y) {
	return center + Vec2(x, y);
}

void SlotMachineController::MenuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}
