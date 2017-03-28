#include "PaddleKeyboardInputComp.h"

PaddleKeyboardInputComp::PaddleKeyboardInputComp(SDL_Keycode up_key,
		SDL_Keycode down_key, SDL_Keycode stop_key, unsigned int velocity) :
		InputComponent() {
	up_key_ = up_key;
	down_key_ = down_key;
	stop_key_ = stop_key;
	velocity_ = velocity;
}

void PaddleKeyboardInputComp::init(GameObject* paddle) {
}

//El método handleInput incrementa la velocidad vertical (de la raqueta correspondiente)
void PaddleKeyboardInputComp::handleInput(SDL_Event event, GameObject* paddle) {
	if (event.key.type == up_key_)
		paddle->setDirectionY(velocity_);
	else if (event.key.type == down_key_)
		paddle->setDirectionY(-(int)velocity_);
	else if (event.key.type == stop_key_)
		paddle->setDirectionY(0);
}

PaddleKeyboardInputComp::~PaddleKeyboardInputComp() {
}
/*Es un InputComponent para controlar una raqueta por teclado. La constructora recibe los códigos de las teclas que
hay que usar para mover y parar la raqueta, además recibe las unidades de velocidad que hay que añadir a la
dirección vertical en cada movimiento.

El método handleInput incrementa la velocidad vertical (de la raqueta correspondiente) en velocity unidades si
el jugador pulsa up_key​, decrementa la velocidad vertical en velocity unidades si pulsa down_key y cambia la
velocidad vertical 0 si pulsa stop_key​. El método init cambia la velocidad vertical a 0​. Recuerda que en esta
clase sólo cambiamos la velocidad vertical, no se toca la posición, el PhysicsComponent ​correspondiente se
encarga de cambiar la posición de la raqueta en función de la nueva velocidad.*/