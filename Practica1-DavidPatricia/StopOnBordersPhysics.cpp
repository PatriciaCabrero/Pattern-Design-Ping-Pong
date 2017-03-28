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

	if (right_  && nextPos.getX() >= o->getGame()->getWindowWidth() - o->getWidth()){
		nextPos.setX(o->getGame()->getWindowWidth() - o->getWidth());
		o->setDirectionX(0);
	}
	else if (left_ && nextPos.getX() <= 0){
		nextPos.setX(0);
		o->setDirectionX(0);
	}

	if (top_ && nextPos.getY() >= o->getGame()->getWindowHeight() - o->getHeight()){
		nextPos.setX(o->getGame()->getWindowHeight() - o->getHeight());
		o->setDirectionY(0);
	}
	else if (bottom_ && nextPos.getY() <= 0){
		nextPos.setY(0);
		o->setDirectionY(0);
	}
	// check if we exit from top/bottom
	/*if (top_ && nextPos.getY() <= 0) {
		nextPos.setY(0);
		o->setDirectionY(-1 * o->getDirection().getY());
		wallHitSound_->play();
	*/
	o->setPosition(nextPos);
}