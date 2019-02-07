#pragma once
#include "cocos2d.h"

class WinEffects {
public:
	WinEffects();
	~WinEffects();

	void Enable();
	void Disable();

private:
	cocos2d::Label *winLabel;
	cocos2d::ParticleFireworks *fireworks[2];
};

