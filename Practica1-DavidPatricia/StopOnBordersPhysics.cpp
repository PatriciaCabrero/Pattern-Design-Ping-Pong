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
		//wallHitSound_->play();
	}

	if (bottom_
		&& nextPos.getY()
		>= o->getGame()->getWindowHeight() - o->getHeight()) {
		nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
		o->setDirectionY(0);
		//wallHitSound_->play();
	}

	// check if we exit from left/right
	if (left_ && nextPos.getX() <= 0) {
		nextPos.setX(0);
		o->setPosition(nextPos);
		o->setDirectionX(0);
		//wallHitSound_->play();
	}

	if (right_
		&& nextPos.getX()
		>= o->getGame()->getWindowWidth() - o->getWidth()) {
		nextPos.setX(o->getGame()->getWindowWidth() - o->getWidth());
		o->setDirectionX(0);
		//wallHitSound_->play();
	}

	o->setPosition(nextPos);
}
/*Es un PhysicsComponent que no deja al GameObject correspondiente salir de los bordes de la pista: si la posición
nueva o->getPostion()+o->getDirection() deja a alguna parte del GameObject ​fuera de la pista lo
volvemos a colocar justo al borde correspondiente y cambiamos su dirección correspondiente a 0​. La constructora
recibe cuatro parámetros de tipo boolean​ para indicar de qué bordes no se permite salir, etc.
Vamos a usar este PhysicsComponent​ para que las raquetas no salgan del borde superior e inferior*/