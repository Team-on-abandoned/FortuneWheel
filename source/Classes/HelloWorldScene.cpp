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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem != nullptr &&
		closeItem->getContentSize().width > 0 &&
		closeItem->getContentSize().height > 0
		) {
		closeItem->setPosition(Vec2(
			origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
			origin.y + closeItem->getContentSize().height / 2
		));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("You win!", "fonts/Marker Felt.ttf", 24);
	if (label != nullptr) {
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));
		this->addChild(label, 1);
	}

	auto sprite = Sprite::create("Art\\SlotMachine.png");
	if (sprite != nullptr) {
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		sprite->setContentSize(Size(461, 246));
		this->addChild(sprite, 0);
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}
