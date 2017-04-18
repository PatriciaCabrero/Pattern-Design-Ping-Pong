#include "PaddleMouseInputComp.h"

PaddleMouseInputComp::PaddleMouseInputComp() {
}

PaddleMouseInputComp::~PaddleMouseInputComp() {

}

void PaddleMouseInputComp::init(GameObject* paddle) {
	paddle->setDirectionY(0);
}


void PaddleMouseInputComp::handleInput(SDL_Event event, GameObject* paddle) {
	if (event.type == SDL_MOUSEMOTION){
		paddle->setDirectionY(event.motion.yrel);
	}
}