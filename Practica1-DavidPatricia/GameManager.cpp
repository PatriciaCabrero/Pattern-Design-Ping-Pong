﻿#include <string>
#include <cmath>
#include <random>

#include "GameManager.h"
SDL_Color blanco = { 255, 255, 255, 255 };


GameManager::GameManager(SDLGame* game,GameObject* lPaddle, GameObject* rPaddle) :
		GameObject(game),rPaddle(rPaddle), lPaddle(lPaddle),paredizq(false),paredrch(false) {
	
	font_ = game_->getResources()->getFont(SDLGame::NESChimera16);
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, blanco);
	score1 = score2 = 0;
	puntuaciones.loadFromText(getGame()->getRenderer(),
		std::to_string(score1) + " - " + std::to_string(score2), *font_, blanco);
	pausa = true;
	wallHit = game->getResources()->getSoundEffect(SDLGame::Wall_Hit);
	paddleHit = game->getResources()->getSoundEffect(SDLGame::Paddle_Hit);
	boo = game->getResources()->getMusic(SDLGame::Boooo);
	cheers = game->getResources()->getMusic(SDLGame::Cheer);
	beat = game->getResources()->getMusic(SDLGame::Beat);
	//careless = game->getResources()->getMusic(SDLGame::Beat);
	SDL_Color rojo = { 255, 0, 0, 255 };
	powerup = new RectRender(rojo);
	width_ = 20;
	height_ = getGame()->getWindowHeight();

}

GameManager::~GameManager() {
}

void GameManager::update() {
}

void GameManager::handleInput(const SDL_Event& event) {
	if (pausa && event.key.keysym.sym == SDLK_SPACE){
		startMsgTexture_.close();
		winner.close();
		pausa = false;
		if (score1 == 0 && score2 == 0) {
			puntuaciones.loadFromText(getGame()->getRenderer(),
				std::to_string(score1) + " - " + std::to_string(score2), *font_, blanco);
			last_paddle_hit_ = nullptr;
			for each(GameStateObserver* obs in observers) {
				obs->onGameStart();
			}
		}
		else {
			last_paddle_hit_ = nullptr;
			for each(GameStateObserver* obs in observers) {
				obs->onRoundStart();
			}
		}
	}
}

void GameManager::render() {

	// just an example, should be adjusted to the requirements!
	startMsgTexture_.render(getGame()->getRenderer(), (getGame()->getWindowWidth()-startMsgTexture_.getWidth())/ 2, getGame()->getWindowHeight()-40);
	winner.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - startMsgTexture_.getWidth()) / 2, getGame()->getWindowHeight() - 80);
	puntuaciones.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - puntuaciones.getWidth()) / 2, 40);

	if (paredizq){
		pos_.setX(0);
		pos_.setY(0);
		powerup->render(this);
	}
	else if (paredrch){
		pos_.setY(0);
		pos_.setX(getGame()->getWindowWidth() - width_);
		powerup->render(this);
	}
}

void GameManager::onCollision(GameObject* ball, GameObject* o) {
	last_paddle_hit_ = o;
	paddleHit->play();
}

void GameManager::onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side) {
	//Arriba o abajo
	if (side == BallObserver::BOT || side == BallObserver::TOP)wallHit->play();

	//Lados
	else {
		if (!paredizq && side == BallObserver::LEFT) {
			score2++;
			boo->play(1);
			finPartida();
		}
		else if (!paredrch && side == BallObserver::RIGHT) {
			score1++;
			cheers->play(1);
			finPartida();
		} else 
		
	}
}
void GameManager::finPartida(){
	pausa = true;
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
		"Press Space to Start", *font_, blanco);
	puntuaciones.loadFromText(getGame()->getRenderer(),
		std::to_string(score1) + " - " + std::to_string(score2), *font_, blanco);
	paredizq =  paredrch = false;

	if (score1 >= 5) {
		beat->play(2);
		score1 = score2 = 0;
		for each(GameStateObserver* obs in observers) {
			obs->onGameOver();
		}
		winner.loadFromText(getGame()->getRenderer(),
			"Player 1 won this time!", *font_, blanco);
	}

	else if (score2 >= 5) {
		beat->play(2);
		score1 = score2 = 0;
		for each(GameStateObserver* obs in observers) {
			obs->onGameOver();
		}
		winner.loadFromText(getGame()->getRenderer(),
			"Player 2 won this time!", *font_, blanco);
	}
	else {
		for each(GameStateObserver* obs in observers) {
			obs->onRoundOver();
		}
	}
}
void GameManager::registerGameStateObserver(GameStateObserver* o) {
	observers.push_back(o);
}

void GameManager::onObstacleCollision(GameObject* obs, GameObject* o){
	if (last_paddle_hit_ == lPaddle) paredizq = true;
	else if (last_paddle_hit_ == rPaddle) paredrch = true;
}//Falta cambiarlo a FALSE

void GameManager::onObstacleStateChange(GameObject* obs, bool state){
	if (!obs->isActive()) {
		paredizq = paredrch = false;
	}
}
/*Cambia la clase GameManager ​para que sea un TimedObstacleObserver. ​Cada vez que reciba un
aviso que la bola ha chocado con el obstáculo, se tiene que “poner una pared” en el borde donde está el
jugador que ha tocado la bola último. Eso evita que la bola salga de ese borde, es decir dando ventaja a
ese jugador. Cuando se desactiva el obstáculo se tiene que quitar esa pared. Observe que la existencia de
una pared simplemente se indica con una variable boolean en el GameManager y se usa para no parar el
juego en ese caso, no hay que crear un nuevo objeto de juego que representa la pared, etc.
Para indicar la existencia de una pared visualmente se puede dibujar una línea en el borde correspondiente
o simplement mostrar un mensaje adecuado a lado del marcador, etc. Hay también que reproducir alguna
música durante el tiempo en el que existe la pared.
*/