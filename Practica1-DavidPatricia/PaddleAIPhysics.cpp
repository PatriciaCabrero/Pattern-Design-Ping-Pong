#include "PaddleAIPhysics.h"


PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
		ball_(ball) {
	speedY = 5;
}

PaddleAIPhysics::~PaddleAIPhysics() {
}

void PaddleAIPhysics::init(GameObject* paddle) {
}

void PaddleAIPhysics::update(GameObject* paddle) {
	int medioCentroOfensivo = paddle->getGame()->getWindowHeight() / 2;
	if (ball_->getPosition().getX() <= paddle->getPosition().getX()){//PALA DERECHA
		if (ball_->getDirection().getX() > 0)//Me estoy acercando
		{
			int  y_pred​;
			int dist = abs(paddle->getPosition().getX()- ball_->getPosition().getX());
			if (dist != 0) {
				int tiempo = ball_->getDirection().getX() / dist;
				y_pred​ = ball_->getPosition().getY() + tiempo* paddle->getDirection().getY();
				while (y_pred​ < 0 || y_pred​ > paddle->getGame()->getWindowHeight()) {
					if (y_pred​ < 0) y_pred​ = abs(y_pred​);
					else if (y_pred​ > paddle->getGame()->getWindowHeight()) y_pred​ -= 2 * (y_pred​ - paddle->getGame()->getWindowHeight());
				}
				if (y_pred​ == paddle->getPosition().getY() + paddle->getHeight() / 2) paddle->setDirectionY(0);
				else if (y_pred​ > paddle->getPosition().getY() + paddle->getHeight() / 2)paddle->setDirectionY(speedY);
				else paddle->setDirectionY(-speedY);
			}

		}
		else//Me alejo
		{
			if (paddle->getPosition().getY() + paddle->getHeight() / 2 == medioCentroOfensivo)paddle->setDirection(0, 0);
			else if (paddle->getPosition().getY() + paddle->getHeight() / 2 > medioCentroOfensivo)paddle->setDirection(0, -speedY);
			else paddle->setDirectionY(speedY);
		}
	
	}
	else//PALA IZQUIERDA
	{
		if (ball_->getDirection().getX() < 0)//Me estoy acercando
		{
			int  y_pred​;
			int dist = abs(paddle->getPosition().getX() - ball_->getPosition().getX());
			if (dist != 0) {
				int tiempo = ball_->getDirection().getX() / dist;
				y_pred​ = ball_->getPosition().getY() + tiempo* paddle->getDirection().getY();
				while (y_pred​ < 0 || y_pred​ > paddle->getGame()->getWindowHeight()) {
					if (y_pred​ < 0) y_pred​ = abs(y_pred​);
					else if (y_pred​ > paddle->getGame()->getWindowHeight()) y_pred​ -= 2 * (y_pred​ - paddle->getGame()->getWindowHeight());
				}
				if (y_pred​ == paddle->getPosition().getY() + paddle->getHeight() / 2) paddle->setDirectionY(0);
				else if (y_pred​ > paddle->getPosition().getY() + paddle->getHeight() / 2)paddle->setDirectionY(speedY);
				else paddle->setDirectionY(-speedY);
			}
		}
		else //Me alejo
		{
			if (paddle->getPosition().getY() + paddle->getHeight() / 2 == medioCentroOfensivo)paddle->setDirection(0, 0);
			else if (paddle->getPosition().getY() + paddle->getHeight() / 2 > medioCentroOfensivo)paddle->setDirection(0, -speedY);
			else paddle->setDirectionY(speedY);
		}
	}
	if(paddle->getPosition().getY() + paddle->getDirection().getY() > 0 && paddle->getPosition().getY() + paddle->getDirection().getY() + paddle->getHeight() < medioCentroOfensivo*2)
		paddle->setPosition(paddle->getPosition() + paddle->getDirection());
}