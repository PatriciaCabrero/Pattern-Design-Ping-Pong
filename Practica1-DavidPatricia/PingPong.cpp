#include "PingPong.h"
#include "BounceOnBorders.h"
#include "RectRender.h"
#include "ImageRendered.h"
#include "StopOnBordersPhysics.h"
#include "PaddleKeyboardInputComp.h"
#include "PaddleMouseInputComp.h"
#include "PaddleAIPhysics.h"


PingPong::PingPong() :
		SDLGame("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

PingPong::~PingPong() {
	closeGame();
}

void PingPong::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	SDL_Color color = { 255, 255, 255, 255 };

	rectangleRenderer_ = new RectRender(color);
	imageRenderer_ = new ImageRendered( getResources()->getTexture(SDLGame::TennisBall));
	mouseRend_ = new ImageRendered(getResources()->getTexture(SDLGame::MouseIcon));
	keyboardRend_ = new ImageRendered(getResources()->getTexture(SDLGame::KeyBoardIcon));
	brainRend_ = new ImageRendered(getResources()->getTexture(SDLGame::AIIcon));

	bounceOnBorderPhysics_ = new BounceOnBorders(true, true, true, true);
	stopOnBorderPhysics_ = new StopOnBordersPhysics(false, false, true, true);
	leftInputKeyboard_ = new PaddleKeyboardInputComp(SDLK_a, SDLK_z, SDLK_s, 5);
	InputMouse_ = new PaddleMouseInputComp();
	rightInputKeyboard_ = new PaddleKeyboardInputComp(SDLK_UP, SDLK_DOWN,  SDLK_SPACE, 5);

	// ball
	ball_ = new GameComponent(this);
	ball_->setWidth(10);
	ball_->setHeight(10);
	ball_->setDirection(0,0); // change to  (0,0) at the end
	ball_->setPosition(
			ball_->getGame()->getWindowWidth() / 2 - ball_->getWidth() / 2,
			ball_->getGame()->getWindowHeight() / 2 - ball_->getHeight() / 2);

	ball_->setRenderComponent(rectangleRenderer_);
	// use the following for an image of a tennis ball
	// ball_->setRenderComponent(imageRenderer_);

	aiPaddlePhysics_ = new PaddleAIPhysics(ball_);
	

	// left paddle
	left_paddle_ = new GameComponent(this);
	left_paddle_->setWidth(10);
	left_paddle_->setHeight(60);
	left_paddle_->setPosition(30,
			(getWindowHeight() - left_paddle_->getHeight()) / 2);
	left_paddle_->setDirection(0, 0);

	// right paddle
	right_paddle_ = new GameComponent(this);
	right_paddle_->setWidth(10);
	right_paddle_->setHeight(60);
	right_paddle_->setPosition(getWindowWidth() - 40,
			(getWindowHeight() - right_paddle_->getHeight()) / 2);
	right_paddle_->setDirection(0, 0);

	//Ball physic component
	pingPongPhysics_ = new PingPongPhysics(left_paddle_, right_paddle_);
	pingPongPhysics_->init(ball_);
	ball_->setPhysicsComponent(pingPongPhysics_);

	//Switcher right
	rightPcompSw_ = new ComponentSwitcher(this,right_paddle_,SDLK_2);
	rightPcompSw_->setPosition(getWindowWidth() - 70, 20);
	rightPcompSw_->setDirection(0, 0);
	rightPcompSw_->setWidth(50);
	rightPcompSw_->setHeight(50);
	rightPcompSw_->addMode(rightInputKeyboard_,stopOnBorderPhysics_, rectangleRenderer_, keyboardRend_);
	rightPcompSw_->addMode(InputMouse_, stopOnBorderPhysics_, rectangleRenderer_, mouseRend_);
	rightPcompSw_->addMode(nullptr, aiPaddlePhysics_, rectangleRenderer_, brainRend_);
	rightPcompSw_->setMode(0);

	//Switcher left
	leftPcompSw_ = new ComponentSwitcher(this, left_paddle_, SDLK_1);
	leftPcompSw_->setPosition(20, 20);
	leftPcompSw_->setDirection(0, 0);
	leftPcompSw_->setWidth(50);
	leftPcompSw_->setHeight(50);
	leftPcompSw_->addMode(leftInputKeyboard_, stopOnBorderPhysics_, rectangleRenderer_, keyboardRend_);
	leftPcompSw_->addMode(InputMouse_, stopOnBorderPhysics_, rectangleRenderer_, mouseRend_);
	leftPcompSw_->addMode(nullptr, aiPaddlePhysics_, rectangleRenderer_, brainRend_);
	leftPcompSw_->setMode(0);

	// game manager
	gameManager_ = new GameManager(this);
	pingPongPhysics_->resgisterBallObserver(gameManager_);
	gameManager_->registerGameStateObserver(pingPongPhysics_);
	actors_.push_back(left_paddle_);
	actors_.push_back(right_paddle_);
	actors_.push_back(ball_);
	actors_.push_back(gameManager_);
	actors_.push_back(rightPcompSw_);
	actors_.push_back(leftPcompSw_);
}

void PingPong::closeGame() {
	delete right_paddle_;
	delete left_paddle_;
	delete ball_;
	delete rectangleRenderer_;
	delete imageRenderer_;
	delete bounceOnBorderPhysics_;
	delete stopOnBorderPhysics_;
	delete leftInputKeyboard_;
	delete rightInputKeyboard_;
	delete InputMouse_;
	delete rightPcompSw_;
}

void PingPong::start() {
	exit_ = false;
	while (!exit_) {
		handleInput();
		update();
		render();
		SDL_Delay(10);
	}
}

void PingPong::stop() {
	exit_ = true;
}

void PingPong::update() {
	for (unsigned int i = 0; i < actors_.size(); i++) {
		actors_[i]->update();
	}
}

void PingPong::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (unsigned int i = 0; i < actors_.size(); i++) {
			actors_[i]->handleInput(event);
		}

	}
}

void PingPong::render() {
	SDL_SetRenderDrawColor(getRenderer(), 0, 100, 100, 255);  // Dark grey.
	SDL_RenderClear(getRenderer());

	for (unsigned int i = 0; i < actors_.size(); i++) {
		actors_[i]->render();
	}
	SDL_RenderPresent(getRenderer());
}

