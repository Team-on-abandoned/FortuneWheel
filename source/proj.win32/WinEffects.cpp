#include "WinEffects.h"
#include "Settings.h"

USING_NS_CC;

void WinEffects::Init(cocos2d::Scene * scene, cocos2d::Vec2 pos) {
	winLabel = Label::createWithTTF("You win!", "fonts/Marker Felt.ttf", 90);
	winLabel->enableShadow();
	winLabel->setPosition(pos);

	fireworks[0] = ParticleFireworks::create();
	fireworks[0]->setPosition(pos - Vec2(winLabel->getContentSize().width / 2 + 10, 0));
	fireworks[1] = ParticleFireworks::create();
	fireworks[1]->setPosition(pos + Vec2(winLabel->getContentSize().width / 2 + 10, 0));

	Disable();

	scene->addChild(winLabel, Settings::z_label_win);
	scene->addChild(fireworks[0], Settings::z_particle_fireworks);
	scene->addChild(fireworks[1], Settings::z_particle_fireworks);
}

void WinEffects::Enable() {
	winLabel->setOpacity(255);
	fireworks[0]->start();
	fireworks[1]->start();
}

void WinEffects::Disable() {
	winLabel->setOpacity(0);
	fireworks[0]->stop();
	fireworks[1]->stop();
}
