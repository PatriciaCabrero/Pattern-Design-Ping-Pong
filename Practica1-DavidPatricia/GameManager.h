#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "SDLGame.h"
#include "GameObject.h"
#include "BallObserver.h"
#include "GameStateObserver.h"
#include "Font.h"
#include "Texture.h"

class GameManager: public GameObject, public BallObserver {

public:
	GameManager(SDLGame* game, GameObject* lPaddle, GameObject* rPaddle);
	virtual ~GameManager();

	virtual void registerGameStateObserver(GameStateObserver* o);

	// from GameObject
	virtual void handleInput(const SDL_Event& e);
	virtual void update();
	virtual void render();

	// from BallObserver
	virtual void onCollision(GameObject* ball, GameObject* o);
	virtual void onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side);

private:
	Font* font_;
	Texture startMsgTexture_;
	Texture puntuaciones;
	Texture winner;
	SoundEffect* wallHit;
	SoundEffect* paddleHit;
	Music* boo;
	Music* cheers;
	Music* beat;
	bool pausa;
	int score1, score2;
	std::vector<GameStateObserver*> observers;
	GameObject* lPaddle;
	GameObject* rPaddle;
	GameObject* last_paddle_hit_;

};

#endif /* SCOREBOARD_H_ */
