#include "ComponentSwitcher.h"

ComponentSwitcher::ComponentSwitcher(SDLGame* game, GameComponent* actor,
		SDL_Keycode ctrlKey) :
		GameObject(game), actor_(actor), ctrlKey_(ctrlKey) {
}

ComponentSwitcher::~ComponentSwitcher() {
}

void ComponentSwitcher::update() {
}

void ComponentSwitcher::handleInput(const SDL_Event& event) {
}

void ComponentSwitcher::addMode(InputComponent* inputComp,
		PhysicsComponent* physicsComp, RenderComponent* renderComp,
		RenderComponent* modeRendered) {
}

void ComponentSwitcher::setMode(int mode) {
}

void ComponentSwitcher::switchToNext() {
}

void ComponentSwitcher::render() {
}
/*
Es un GameObject que permite cambiar el InputComponent​, PhysicsComponent y RenderComponent ​de un
GameComponent ​durante el juego. La vamos a usar para permitir cambiar el modo de cada raqueta. La constructora
recibe dos parámetros: un actor que representa el GameComponent ​que queremos controlar y un código de tecla
ctrlKey​ que se debe usar para cambiar al modo siguiente.

Cada modo es una cuádruple:

		[ InputComponent* inputComp, PhysicsComponent* physicsComp,
			RenderComponent* renderComp,RenderComponent* modeRendered ]

Pasar a un modo significa cambiar los InputComponent,​ PhysicsComponent y RenderComponent ​de actor a
los inputComp​, physicsComp y renderComp ​correspondientes. Además, el ComponentSwitcher tiene que
empezar a usar el modeRendered ​para dibujarse (como los iconos de teclado y ratón en la figura).
Internamente ComponentSwitcher tiene que mantener una lista de modos (por ejemplo usando std::vector​).
La posición en la lista es el identificador del modo. El método addMode ​permite añadir un modo y el método setMode
permite cambiar de modo (por ejemplo para fijar el modo inicial desde fuera). El método handleInput de
ComponentSwitcher ​tiene que cambiar al modo siguiente si detecta un pulse sobre ctrlKey​. El siguiente del
último modo es el primero.*/