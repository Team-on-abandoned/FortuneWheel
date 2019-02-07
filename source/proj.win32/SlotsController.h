#pragma once
#include "cocos2d.h"
#include <vector>
#include "Slot.h"

class SlotsController {
public:
	SlotsController();
	~SlotsController();

	//������� ������� ��� ��� �����
	void AddSprite(cocos2d::Sprite sprite);
	//������� ���� �� ������� slotPos. ���������� ���� ���� ��� ������� AddSprite().
	void AddSlot(cocos2d::Vec2 slotPos);

	//������ ������ 2 ������ Roll() ���������
	void EnableDebugMode();
	void DisableDebugMode();

	void Roll();

	bool IsWin();

private:
	std::vector<cocos2d::Sprite*> sprites;
	std::vector<Slot> slots;

	float durationForRoll;
	char  maxRotates;

	bool isInDebugMode;

	void RollSlot(char slotNum, float duration, char rotates);
	void RollSlotRec(char slotNum, float durationForRotate, char rotates);
};
