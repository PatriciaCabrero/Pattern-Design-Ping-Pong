#include "PaddleAIPhysics.h"


PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
		ball_(ball) {
}

PaddleAIPhysics::~PaddleAIPhysics() {
}

void PaddleAIPhysics::init(GameObject* paddle) {
}

void PaddleAIPhysics::update(GameObject* paddle) {
	if (ball_->getPosition().getX() <= paddle->getPosition().getX()){//PALA DERECHA
		if (ball_->getDirection().getX() > 0)//Me estoy acercando
		{
			int  y_pred​;
			int dist = paddle->getPosition().getX()- ball_->getPosition().getX();
			int tiempo = ball_->getDirection().getX() / dist;
			y_pred​ = tiempo* paddle->getDirection().getY();
			if ((y_pred​ < paddle->getPosition().getY() && paddle->getDirection().getY() > 0) || 
				(y_pred​ > paddle->getPosition().getY() && paddle->getDirection().getY() < 0)){
				paddle->setDirectionY(-paddle->getDirection().getY());
			}

		}
		else//Me alejo
		{
			if ((paddle->getPosition().getY() < paddle->getGame()->getWindowHeight() / 2 && paddle->getDirection().getY() < 0) ||
				(paddle->getPosition().getY() > paddle->getGame()->getWindowHeight() / 2 && paddle->getDirection().getY() > 0)){
				paddle->setDirectionY(-paddle->getDirection().getY());
			}
		}
	
	}
	else//PALA IZQUIERDA
	{
		if (ball_->getDirection().getX() < 0)//Me estoy acercando
		{
			int  y_pred​;
			int dist = paddle->getPosition().getX() - ball_->getPosition().getX();
			int tiempo = ball_->getDirection().getX() / dist;
			y_pred​ = tiempo* paddle->getDirection().getY();
			if ((y_pred​ < paddle->getPosition().getY() && paddle->getDirection().getY() > 0) ||
				(y_pred​ > paddle->getPosition().getY() && paddle->getDirection().getY() < 0)){
				paddle->setDirectionY(-paddle->getDirection().getY());
			}

		}
		else //Me alejo
		{
			if ((paddle->getPosition().getY() < paddle->getGame()->getWindowHeight() / 2 && paddle->getDirection().getY() < 0) ||
				(paddle->getPosition().getY() > paddle->getGame()->getWindowHeight() / 2 && paddle->getDirection().getY() > 0)){
				paddle->setDirectionY(- paddle->getDirection().getY());
			}
		}
	}
}

/*Es un PhysicsComponent para controlar una raqueta automáticamente usando un algoritmo sencillo. La
constructora recibe un GameObject ​que representa la bola para poder consultar su posición y dirección actual en el
algoritmo.
El método update​ calcula la siguiente posición de la raqueta usando los siguientes pasos:
1. Si la bola no avanza hacia el lado de la raqueta avanzamos la raqueta hacia el centro vertical;
2. Si la bola avanza hacia el lado de la raqueta, calculamos una predicción y_pred de la posición vertical de la
bola cuando llegue al lado de la raqueta y avanzamos la raqueta hacia la posición y_pred​.
Para la predicción de la posición vertical de la bola se puede usar simplemente la posición vertical actual de la bola o
implementar algo más inteligente. Recuerda que la posición horizontal de las raquetas nunca cambia.*/