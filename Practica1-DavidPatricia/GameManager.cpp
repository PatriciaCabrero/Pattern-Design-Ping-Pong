#include <string>
#include <cmath>
#include <random>

#include "GameManager.h"


GameManager::GameManager(SDLGame* game) :
		GameObject(game) {
	font_ = game_->getResources()->getFont(SDLGame::NESChimera16);
	SDL_Color color = { 255, 255, 255, 255 };
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);
	score1 = score2 = 0;
}

GameManager::~GameManager() {
}

void GameManager::update() {
}

void GameManager::handleInput(const SDL_Event& event) {
	if (event.key.keysym.sym == SDLK_SPACE){
		if (score1 == score2 == 0) {
			for each(GameStateObserver* obs in observers) {
				obs->onGameStart();
			}
		}
		else {
			for each(GameStateObserver* obs in observers) {
				obs->onRoundStart();
			}
		}
	}
}

void GameManager::render() {

	// just an example, should be adjusted to the requirements!
	startMsgTexture_.render(getGame()->getRenderer(), (getGame()->getWindowWidth()-startMsgTexture_.getWidth())/ 2, getGame()->getWindowHeight()-40);
	puntuaciones.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - puntuaciones.getWidth()) / 2, 40);
}

void GameManager::onCollision(GameObject* ball, GameObject* o) {

}

void GameManager::onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side) {
	SDL_Color color = { 255, 255, 255, 255 };
	if (side == BallObserver::LEFT)score2++;
	else if (side == BallObserver::RIGHT)score1++;
	puntuaciones.loadFromText(getGame()->getRenderer(),
		std::to_string(score1) + " - " + std::to_string(score2), *font_, color);
	if (score1 == 5) {
		for each(GameStateObserver* obs in observers) {
			obs->onRoundOver(ball);
		}
	}else if (score2 == 5) {
		for each(GameStateObserver* obs in observers) {
			obs->onRoundOver(ball);
		}
	}
}

void GameManager::registerGameStateObserver(GameStateObserver* o) {
	observers.push_back(o);
}
