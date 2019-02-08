#include "SlotMachineHandle.h"
#include "Settings.h"
USING_NS_CC;


SlotMachineHandle::SlotMachineHandle() :
	isHandleDown(false),
	downMouseOnHandle(false),
	mouseListener(EventListenerMouse::create()) {
}


SlotMachineHandle::~SlotMachineHandle() {
}

void SlotMachineHandle::Init(cocos2d::Scene * scene, cocos2d::Vec2 handlePos, cocos2d::Vec2 handleDownPos) {
	this->scene = scene;

	handleUp = Sprite::create("Art\\knob1.png");
	handleUp->setPosition(handlePos);
	scene->addChild(handleUp, Settings::z_sprite_handle);

	handleUpActive = Sprite::create("Art\\KnobGlowHL.png");
	handleUpActive->setPosition(handlePos);
	handleUpActive->setOpacity(0);
	scene->addChild(handleUpActive, Settings::z_sprite_handleGlow);

	handleDown = Sprite::create("Art\\KnobDown.png");
	handleDown->setPosition(handleDownPos);
	handleDown->setContentSize(handleDown->getContentSize());
	handleDown->setOpacity(0);
	scene->addChild(handleDown, Settings::z_sprite_handleDown);

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(SlotMachineHandle::HandleMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(SlotMachineHandle::HandleMouseUp, this);
	listener->onMouseMove = CC_CALLBACK_1(SlotMachineHandle::GlowHandle, this);

	scene->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

void SlotMachineHandle::Link(SlotsController * _slotsController, TokenInfo * _tokenInfo, WinEffects *_winEffects) {
	slotsController = _slotsController;
	tokenInfo = _tokenInfo;
	winEffects = _winEffects;
}

void SlotMachineHandle::HandleDown() {
	isHandleDown = true;
	handleUp->setOpacity(0);
	handleUpActive->setOpacity(0);
	handleDown->setOpacity(255);
}

void SlotMachineHandle::HandleUp() {
	isHandleDown = false;
	handleUp->setOpacity(255);
	handleUpActive->setOpacity(0);
	handleDown->setOpacity(0);
}

void SlotMachineHandle::GlowHandle(cocos2d::Event * event) {
	EventMouse* e = (EventMouse*)event;
	if (!isHandleDown && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		handleUpActive->setOpacity(255);
	}
	else {
		handleUpActive->setOpacity(0);
	}
}

void SlotMachineHandle::HandleMouseDown(cocos2d::Event * event) {
	EventMouse* e = (EventMouse*)event;
	if (pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2))
		downMouseOnHandle = true;
}

void SlotMachineHandle::HandleMouseUp(cocos2d::Event * event) {
	EventMouse* e = (EventMouse*)event;
	if (downMouseOnHandle && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		downMouseOnHandle = false;

		if (!slotsController->GetIsAnimationPlaying()) {
			winEffects->Disable();
			this->HandleDown();
			tokenInfo->PlayAnimation();
			scene->runAction(Sequence::createWithTwoActions(DelayTime::create(1), CallFunc::create([this]() {this->HandleUp();})));
		}
	}
}
