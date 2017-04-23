#include "StopOnBordersPhysics.h"

StopOnBordersPhysics::StopOnBordersPhysics(bool left, bool right, bool top,
		bool bottom) :
		left_(left), right_(right), top_(top), bottom_(bottom) {
}

StopOnBordersPhysics::~StopOnBordersPhysics() {
}

void StopOnBordersPhysics::init(GameObject* o) {

}


void StopOnBordersPhysics::update(GameObject* o) {
	Vector2D<int> nextPos = o->getPosition() + o->getDirection();

	// check if we exit from top/bottom
	if (top_ && nextPos.getY() <= 0) {
		nextPos.setY(0);
		o->setPosition(nextPos);
		o->setDirectionY(0);
	}

	if (bottom_
		&& nextPos.getY()
		>= o->getGame()->getWindowHeight() - o->getHeight()) {
		nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
		o->setDirectionY(0);
	}

	// check if we exit from left/right
	if (left_ && nextPos.getX() <= 0) {
		nextPos.setX(0);
		o->setPosition(nextPos);
		o->setDirectionX(0);
	}

	if (right_
		&& nextPos.getX()
		>= o->getGame()->getWindowWidth() - o->getWidth()) {
		nextPos.setX(o->getGame()->getWindowWidth() - o->getWidth());
		o->setDirectionX(0);
	}

	o->setPosition(nextPos);
}