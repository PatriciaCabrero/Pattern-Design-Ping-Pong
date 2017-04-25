#pragma once
#include "GameObject.h"
class TimedObstacleObserver {
public:
	TimedObstacleObserver();
	virtual ~TimedObstacleObserver();
	//El método onObstacleStateChange ​se usa para avisar a los observadores cuando se activa / desactiva el obstáculo.
	virtual void onObstacleStateChange(GameObject* obs, bool state) = 0;
	//El método onObstacleCollision se usa para avisar a los observadores que el objeto o (la bola en nuestro caso) ha chocado con el obstáculo obs​.
	virtual void onObstacleCollision(GameObject* obs, GameObject* o) = 0;
};