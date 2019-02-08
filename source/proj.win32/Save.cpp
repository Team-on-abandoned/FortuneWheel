#include <iostream>
#include "Save.h"

USING_NS_CC;
using std::cout;
using std::endl;

Scene* Save::createScene() {
	return Save::create();
}

bool Save::init() {
	if (!Scene::init())
		return false;

	handleIsDown = animationPlaying = downMouseOnHandle = false;

	mouseListener = EventListenerMouse::create();

	return true;
}


void Save::GlowHandle(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (!handleIsDown && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		handleUpActive->setOpacity(255);
	}
	else {
		handleUpActive->setOpacity(0);
	}
}

void Save::HandleMouseDown(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2))
		downMouseOnHandle = true;
}

void Save::HandleMouseUp(Event *event) {
	EventMouse* e = (EventMouse*)event;
	if (downMouseOnHandle && pow(e->getCursorX() - handleUp->getPositionX(), 2) + pow(e->getCursorY() - handleUp->getPositionY(), 2) <= pow(handleUp->getContentSize().height / 2, 2)) {
		downMouseOnHandle = false;

		if (!animationPlaying) {
			winLabel->setOpacity(0);
			fireworks[0]->stop();
			fireworks[1]->stop();

			animationPlaying = handleIsDown = true;
			handleUp->setOpacity(0);
			handleUpActive->setOpacity(0);
			handleDown->setOpacity(255);

			//PlayCoinAnimation();
		}
	}

}
