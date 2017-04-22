#include <cmath>
#include <random>
#include "PingPongPhysics.h"

PingPongPhysics::PingPongPhysics(GameObject* left_paddle,
		GameObject* right_paddle) :
		left_paddle_(left_paddle), right_paddle_(right_paddle), hits_(
				0), speed_(8) {
}

PingPongPhysics::~PingPongPhysics() {
}

void PingPongPhysics::init(GameObject* o) {
}

void PingPongPhysics::update(GameObject* o) {
	Vector2D<int> nextPos = o->getPosition() + o->getDirection();
	//Pelota colisiona con pala derecha
	if (o->getDirection().getX() > 0
		&& nextPos.getX() + o->getWidth() > right_paddle_->getPosition().getX() 
		&& nextPos.getY() > right_paddle_->getPosition().getY() - o->getHeight() 
		&& nextPos.getY() < right_paddle_->getPosition().getY() + right_paddle_->getHeight()) {
		hits_++;
		/*o->setDirectionX(-o->getDirection().getX());*/
		actualizaDir(o, right_paddle_);
		nextPos = o->getPosition() + o->getDirection();
		for each (BallObserver* obs in observers)
		{
			obs->onCollision(o, right_paddle_);
		}
	}
	//Pelota colisiona con pala izquierda
	else if (o->getDirection().getX() < 0
		&& nextPos.getX() < left_paddle_->getPosition().getX() + left_paddle_->getWidth()
		&& nextPos.getY() > left_paddle_->getPosition().getY() - o->getHeight()
		&& nextPos.getY() < left_paddle_->getPosition().getY() + left_paddle_->getHeight()) {
		hits_++;
		//o->setDirectionX(-o->getDirection().getX());
		actualizaDir(o, left_paddle_);
		nextPos = o->getPosition() + o->getDirection();
		for each (BallObserver* obs in observers)
		{
			obs->onCollision(o, left_paddle_);
		}
	}
	//Borde superior
	if (nextPos.getY() <= 0) {
		nextPos.setY(0);
		o->setPosition(nextPos);
		o->setDirectionY(-1 * o->getDirection().getY());
		//wallHitSound_->play();
	}
	//Borde inferior
	if (nextPos.getY() >= o->getGame()->getWindowHeight() - o->getHeight()) {
		nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
		o->setDirectionY(-1 * o->getDirection().getY());
		//wallHitSound_->play();
	}

	//Borde izquierdo
	if (nextPos.getX() <= 0) {//KEPPPASAAkI
		nextPos.setX(0);
		o->setPosition(nextPos);
		o->setDirectionX(-1 * o->getDirection().getX());
		for each (BallObserver* obs in observers)
		{
			obs->onBorderExit(o,BallObserver::LEFT);
		}
		//wallHitSound_->play();
	}
	//Borde derecho
	if (nextPos.getX() >= o->getGame()->getWindowWidth() - o->getWidth()) {//KEPPPASAAkI
		nextPos.setX(o->getGame()->getWindowWidth() - o->getWidth());
		o->setDirectionX(-1 * o->getDirection().getX());
		for each (BallObserver* obs in observers)
		{
			obs->onBorderExit(o, BallObserver::RIGHT);
		}
		//wallHitSound_->play();
	}

	if (hits_ == 5) {
		hits_ = 0;
		speed_++;
	}
	o->setPosition(nextPos);
}

void PingPongPhysics::actualizaDir(GameObject* ball, GameObject* paddle)
{
	int sign = ball->getDirection().getX() < 0 ? 1 : -1;
	int rel_y = (ball->getPosition().getY() - paddle->getPosition().getY() + ball->getHeight());
	float angle = (2.14f * rel_y - 75.0f);
	int dx = sign * speed_ * std::cos(angle * M_PI / 180.0f);
	int dy = speed_ * std::sin(angle * M_PI / 180.0f);
	ball->setDirection(dx, dy);
}


void PingPongPhysics::resgisterBallObserver(BallObserver* o) {
	observers.push_back(o);
}


void PingPongPhysics::onGameStart() {
}

void PingPongPhysics::onGameOver() {
}

void PingPongPhysics::onRoundStart() {
	hits_ = 0;
	speed_ = 8;
	int direction = 1 - 2 * (rand() % 2);
	int angle = 60 - (rand() % 121);
	int dx = direction * speed_ * std::cos(angle * M_PI / 180.0f);
	int dy = speed_ * std::sin(angle * M_PI / 180.0f);
	//Le pongo la direccion a la pelota
}

void PingPongPhysics::onRoundOver() {
	//Direccion de la pelota a 0,0
	//Posicion a centro pista
}

