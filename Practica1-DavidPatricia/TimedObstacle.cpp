#include "TimedObstacle.h"
#include "RectRender.h"


TimedObstacle::TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball) : 
GameObject(game), pTime(pTime), dTime(dTime), ball(ball), juegoactivo(false)
{
	SDL_Color color = { 0, 255, 255, 255 };
	renderComp_ = new RectRender(color);
	visible = false;
	juegoactivo = false;
	active_ = false;
}


TimedObstacle::~TimedObstacle()
{
	delete renderComp_;
}

void TimedObstacle::update(){
	if (juegoactivo){
		if (!active_ && last_time_on_ + pTime < SDL_GetTicks()){
			if (rand() % 2 == 0){
				active_ = true;
				visible = true;
				last_time_on_ = SDL_GetTicks();
				for each (TimedObstacleObserver* var in timedObservers)
				{
					var->onObstacleStateChange(this, true);
				}
				//Pos aleatoria
				pos_.set(posAleatoria());
			}
		}
		else if (active_ && last_time_on_ + dTime < SDL_GetTicks()){
			active_ = false;
			visible = false;

			for each (TimedObstacleObserver* var in timedObservers)
			{
				var->onObstacleStateChange(this, false);
			}
		}
		else if (active_&&visible){
			if (compCollision()){
				visible = false;
				for each (TimedObstacleObserver* var in timedObservers)
				{
					var->onObstacleCollision(this, ball);
				}
			}

		}
	}
}

void TimedObstacle::addObserver(TimedObstacleObserver* o){
	timedObservers.push_back(o);	
}

void TimedObstacle::onGameStart(){
	juegoactivo = true;
	active_ = false;
};

void TimedObstacle::onGameOver(){
	juegoactivo = false;
	active_ = false;
	visible = false;
};

void TimedObstacle::onRoundStart(){
	juegoactivo = true;
	active_ = false;
};

void TimedObstacle::onRoundOver(){
	juegoactivo = false;
	active_ = false;
	visible = false;

};
void TimedObstacle::render(){
	if (visible && renderComp_)
		renderComp_->render(this);
};


Vector2D<int> TimedObstacle::posAleatoria(){
	Vector2D<int> aux;
	aux.setX(ball->getGame()->getWindowHeight()* ((float)(rand() % 100) / 100));
	aux.setY((ball->getGame()->getWindowWidth()-height_)* ((float)(rand() % 100) / 100));

	while (aux.getX() > ball->getGame()->getWindowHeight() - 50 || aux.getX()< 50){
		aux.setX(ball->getGame()->getWindowHeight()* ((float)(rand() % 100) / 100));
	}
	return aux;
}

bool TimedObstacle::compCollision(){
	//esquina superior izquierda 
	if (ball->getPosition().getX() > pos_.getX() && ball->getPosition().getX() < pos_.getX() + width_
		&& ball->getPosition().getY() > pos_.getY() && ball->getPosition().getY() < pos_.getY() + height_)
		return true;
	//esquina superior derecha
	else if (ball->getPosition().getX() + ball->getWidth() > pos_.getX() && ball->getPosition().getX() + ball->getWidth() < pos_.getX() + width_
		&& ball->getPosition().getY() > pos_.getY() && ball->getPosition().getY() < pos_.getY() + height_)
		return true;
	//esquina inferior izquierda 
	else if(ball->getPosition().getX() > pos_.getX() && ball->getPosition().getX() < pos_.getX() + width_
		&& ball->getPosition().getY() + ball->getHeight() > pos_.getY() && ball->getPosition().getY() + ball->getHeight() < pos_.getY() + height_)
		return true;
	//esquina inferior derecha
	else if (ball->getPosition().getX() + ball->getWidth() > pos_.getX() && ball->getPosition().getX() + ball->getWidth() < pos_.getX() + width_
		&& ball->getPosition().getY() + ball->getHeight()> pos_.getY() && ball->getPosition().getY() + ball->getHeight() < pos_.getY() + height_)
		return true;
	else return false;
}