#include "TokenInfo.h"
#include "Settings.h"
USING_NS_CC;

void TokenInfo::Init(cocos2d::Scene *scene, cocos2d::Vec2 _tokenStartPos, cocos2d::Vec2 _tokenEndPos, cocos2d::Vec2 _tokenInsertStartPos, cocos2d::Vec2 _tokenInsertEndPos) {
	tokenStartPos = _tokenStartPos;
	tokenEndPos = _tokenEndPos;
	tokenInsertStartPos = _tokenInsertStartPos;
	tokenInsertEndPos = _tokenInsertEndPos;

	token = Sprite::create("Art\\token.png");
	token->setPosition(tokenStartPos);
	scene->addChild(token, Settings::z_sprite_token);

	insertToken = Sprite::create("Art\\insertToken.png");
	insertToken->setPosition(_tokenInsertStartPos);
	insertToken->setOpacity(0);
	scene->addChild(insertToken, Settings::z_sprite_insertToken);
}

void TokenInfo::PlayAnimation() {
	token->runAction(Sequence::create(
		Spawn::create(
			MoveTo::create(2, tokenEndPos),
			Sequence::create(
				DelayTime::create(1),
				CallFunc::create([this]() {
					/*handleUp->setOpacity(255);
					handleDown->setOpacity(0);
					handleIsDown = false;*/
				}),
				nullptr
			),
			nullptr
		),

		CallFunc::create([this]() {
			token->setPosition(tokenStartPos);
			insertToken->setPosition(tokenInsertStartPos);
			insertToken->setOpacity(255);

			insertToken->runAction(Sequence::create(
				MoveTo::create(2, tokenInsertEndPos),
				FadeOut::create(2),
				nullptr
			));
		}),

		nullptr
		));
}
