#include "TimedObstacle.h"


TimedObstacle::TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball) : 
GameObject(game), pTime(pTime), dTime(dTime), ball(ball), juegoactivo(false)
{
}


TimedObstacle::~TimedObstacle()
{
}

void TimedObstacle::update(){
	if (juegoactivo){
		if (!active_ && last_time_on_ + pTime < SDL_GetTicks()){
			if (rand() % 2){
				active_ = true;
				last_time_on_ = SDL_GetTicks();
			}
		}
		else if (active_ && last_time_on_ + dTime < SDL_GetTicks()){

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
};

void TimedObstacle::onRoundStart(){
	juegoactivo = true;
};

void TimedObstacle::onRoundOver(){
	juegoactivo = false;
	active_ = false;
};


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