#pragma once
#include "cocos2d.h"

class TokenInfo {
public:
	TokenInfo();
	~TokenInfo();

	void SetTokenPos(cocos2d::Vec2 tokenStartPos, cocos2d::Vec2 tokenEndPos, cocos2d::Vec2 tokenInsertStartPos, cocos2d::Vec2 tokenInsertEndPos);

	void PlayAnimation();

private:
	cocos2d::Vec2 tokenStartPos, tokenEndPos, tokenInsertStartPos, tokenInsertEndPos;
	cocos2d::Sprite *token, *insertToken;

	float animationDuration;
};

