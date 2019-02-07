#pragma once
#include "cocos2d.h"

class WinEffects {
public:
	void Init(cocos2d::Scene *scene, cocos2d::Vec2 pos);

	void Enable();
	void Disable();

private:
	cocos2d::Label *winLabel;
	cocos2d::ParticleFireworks *fireworks[2];
};

