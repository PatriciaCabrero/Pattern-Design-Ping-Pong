#include <string>
#include <cmath>
#include <random>

#include "GameManager.h"


GameManager::GameManager(SDLGame* game,GameObject* lPaddle, GameObject* rPaddle) :
		GameObject(game),rPaddle(rPaddle), lPaddle(lPaddle) {
	font_ = game_->getResources()->getFont(SDLGame::NESChimera16);
	SDL_Color color = { 255, 255, 255, 255 };
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);
	score1 = score2 = 0;
	puntuaciones.loadFromText(getGame()->getRenderer(),
		std::to_string(score1) + " - " + std::to_string(score2), *font_, color);
	pausa = true;
	wallHit = game->getResources()->getSoundEffect(SDLGame::Wall_Hit);
	paddleHit = game->getResources()->getSoundEffect(SDLGame::Paddle_Hit);
	boo = game->getResources()->getMusic(SDLGame::Boooo);
	cheers = game->getResources()->getMusic(SDLGame::Cheer);
	beat = game->getResources()->getMusic(SDLGame::Beat);
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
			SDL_Color color = { 255, 255, 255, 255 };
			puntuaciones.loadFromText(getGame()->getRenderer(),
				std::to_string(score1) + " - " + std::to_string(score2), *font_, color);
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
		pausa = true;
		SDL_Color color = { 255, 255, 255, 255 };
		startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);

		if (side == BallObserver::LEFT) { 
			score2++;
			boo->play(1);
		}
		else if (side == BallObserver::RIGHT) {
			score1++;
			cheers->play(1);
		}
		puntuaciones.loadFromText(getGame()->getRenderer(),
			std::to_string(score1) + " - " + std::to_string(score2), *font_, color);

		if (score1 >= 5) {
			beat->play(2);
			score1 = score2 = 0;
			for each(GameStateObserver* obs in observers) {
				obs->onGameOver();
			}
			winner.loadFromText(getGame()->getRenderer(),
				"Player 1 won this time!", *font_, color);
		}

		else if (score2 >= 5) {
			beat->play(2);
			score1 = score2 = 0;
			for each(GameStateObserver* obs in observers) {
				obs->onGameOver();
			}
			winner.loadFromText(getGame()->getRenderer(),
				"Player 2 won this time!", *font_, color);
		}
		else {
			for each(GameStateObserver* obs in observers) {
				obs->onRoundOver();
			}
		}
	}
}

void GameManager::registerGameStateObserver(GameStateObserver* o) {
	observers.push_back(o);
}
