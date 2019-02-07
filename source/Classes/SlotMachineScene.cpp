#include <iostream>
#include "SlotMachineScene.h"

USING_NS_CC;

Scene* SlotMachineScene::createScene() {
	return SlotMachineScene::create();
}

bool SlotMachineScene::init() {
	if (!Scene::init())
		return false;

	slotMachineController.StartGame(this);

	return true;
}