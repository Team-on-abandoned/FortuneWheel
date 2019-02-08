#include "Slot.h"
#include "Settings.h"

USING_NS_CC;


Slot::Slot(cocos2d::Scene *scene, cocos2d::Vec2 slotPos, std::vector<cocos2d::Sprite*> _sprites) : currentSprite(0), scene(scene) {
	auto slotBG = Sprite::create("Art\\SlotBG.png");
	slotBG->setPosition(slotPos);
	scene->addChild(slotBG, Settings::z_sprite_slotBG);

	slotFrames[0] = Sprite::create("Art\\Frame.png");
	slotFrames[1] = Sprite::create("Art\\Frame.png");
	for (char j = 0; j < 2; ++j) {
		slotFrames[j]->setPosition(slotPos);
		slotFrames[j]->setPositionY(slotFrames[j]->getPositionY() + j * slotBG->getContentSize().height);
		scene->addChild(slotFrames[j], Settings::z_sprite_slotFrame);
	}

	for(Sprite* s : _sprites)
		sprites.push_back(Sprite::createWithTexture(s->getTexture()));

	for (char j = 0; j < sprites.size(); ++j) {
		sprites[j]->setPosition(slotPos);
		sprites[j]->setPositionY(sprites[j]->getPositionY() + j * slotBG->getContentSize().height);
		scene->addChild(sprites[j], Settings::z_sprite_slotSprite);
	}
}


Slot::~Slot() {
}

void Slot::Roll(float durationForAll, char rotates) {
	RecRoll(durationForAll / rotates, rotates);
}

void Slot::RecRoll(float durationForRotate, char rotates) {
	if (rotates <= 0)
		return;

	for (char i = 0; i < sprites.size(); ++i)
		sprites[i]->runAction(MoveBy::create(durationForRotate, Vec2(0, -(*slotFrames)->getContentSize().height)));

	auto move = MoveBy::create(durationForRotate, Vec2(0, -(*slotFrames)->getContentSize().height));
	auto changeSlotBack = CallFunc::create([this]() {
		auto tmp = slotFrames[0]->getPosition();
		slotFrames[0]->setPosition(slotFrames[1]->getPosition());
		slotFrames[1]->setPosition(slotFrames[0]->getPosition());

	});

	slotFrames[0]->runAction(Sequence::create(move, changeSlotBack, nullptr));

	cocos2d::CallFunc* changeSlotsFigure = cocos2d::CallFunc::create([this, durationForRotate, rotates]() {
		char place = currentSprite - 1;
		if (place == -1)
			place = 4;

		sprites[currentSprite]->setPosition(
			sprites[place]->getPosition() +
			Vec2(0, (*slotFrames)->getContentSize().height)
		);

		if (++currentSprite == 5)
			currentSprite = 0;

		RecRoll(durationForRotate, rotates - 1);
	});

	scene->runAction(Sequence::create(DelayTime::create(durationForRotate), changeSlotsFigure, nullptr));
}
