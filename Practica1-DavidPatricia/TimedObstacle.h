#pragma once
#include "GameObject.h"
#include "GameStateObserver.h"
#include "TimedObstacleObserver.h"
#include "RenderComponent.h"

class TimedObstacle :
	public GameObject, public GameStateObserver
{
public:
	TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball);
	virtual ~TimedObstacle();
	virtual void addObserver(TimedObstacleObserver* o);
	virtual void onGameStart();
	virtual void onGameOver();
	virtual void onRoundStart();
	virtual void onRoundOver();
	virtual void render();

	virtual void update();
	virtual void handleInput(const SDL_Event& event) {};

private:
	RenderComponent* renderComp_;
	int last_time_on_;
	int pTime;
	int dTime; 
	GameObject* ball;
	std::vector <TimedObstacleObserver*> timedObservers;
	bool juegoactivo, visible;
	Vector2D<int> posAleatoria();
	bool compCollision();
};

