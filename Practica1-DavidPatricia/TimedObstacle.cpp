#include "TimedObstacle.h"
#include "RectRender.h"


TimedObstacle::TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball) : 
GameObject(game), pTime(pTime), dTime(dTime), ball(ball), juegoactivo(false)
{
	SDL_Color color = { 255, 255, 255, 255 };
	renderComp_ = new RectRender(color);
}


TimedObstacle::~TimedObstacle()
{
	delete renderComp_;
}

void TimedObstacle::update(){
	if (juegoactivo){
		if (!active_ && last_time_on_ + pTime < SDL_GetTicks()){
			if (rand() % 2){
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

};

void TimedObstacle::onGameOver(){
	juegoactivo = false;
	active_ = false;
	visible = false;

};

void TimedObstacle::onRoundStart(){
	juegoactivo = true;
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
	aux.setY(ball->getGame()->getWindowWidth()* ((float)(rand() % 100) / 100));

	while (aux.getX() > ball->getGame()->getWindowHeight() - 20 || aux.getX()< 20){
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

/*1. Si el juego está en marcha, cada pTime milisegundos si el valor de rand()%2 es cero se activa el
obstáculo para un periodo de dTime milisegundos. Cuando el juego está parado el obstáculo tiene
que ser inactivo y invisible. Observe que la clase TimedObstacle es un GameStateObserver
para poder saber si el juego está en marcha.

2. Cuando se activa el obstáculo se tiene que mostrar un gráfico correspondiente y avisar a los
observadores con un mensaje adecuado. La posición del obstáculo se elige de manera aleatoria cada
vez que se activa --- mejor colocarlo un poco lejos de las raquetas, hacia el centro. Puedes usar
cualquier imagen o simplemente un rectángulo para dibujar el obstáculo.

3. Cuando pasan dTime milisegundos (desde la activación) se tiene que ocultar y desactivar el
obstáculo y avisar a los observadores con un mensaje adecuado.

4. Si la bola choca con el obstáculo mientras esté activo y visible se tiene que ocultar el obstáculo y
avisar a los observadores con un mensaje adecuado. Observe que aunque se oculta, el obstáculo
sigue activo para lo que queda de dTime​. No es obligatorio cambiar la dirección de la bola al chocar
con el obstáculo, puedes hacerlo si quieres.*/