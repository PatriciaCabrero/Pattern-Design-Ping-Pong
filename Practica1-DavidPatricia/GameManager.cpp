#include <string>
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
	careless = game->getResources()->getMusic(SDLGame::Careless);
	SDL_Color rojo = { 255, 0, 0, 255 };
	powerup = new RectRender(rojo);
	width_ = 5;
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
		}
		else wallHit->play();
	}
}

void GameManager::finPartida(){
	pausa = true;
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
		"Press Space to Start", *font_, blanco);
	puntuaciones.loadFromText(getGame()->getRenderer(),
		std::to_string(score1) + " - " + std::to_string(score2), *font_, blanco);
	if (paredizq || paredrch) {
		careless->pause();
		paredizq = paredrch = false;
	}
	//careless->pause();

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
	careless->play(1);
}

void GameManager::onObstacleStateChange(GameObject* obs, bool state){
	if (!obs->isActive()) {
		paredizq = paredrch = false;
		careless->pause();
	}
}