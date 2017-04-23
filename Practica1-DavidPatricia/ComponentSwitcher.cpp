#include "ComponentSwitcher.h"
#include "ImageRendered.h"
#include "RectRender.h"

ComponentSwitcher::ComponentSwitcher(SDLGame* game, GameComponent* actor,
		SDL_Keycode ctrlKey) :
		GameObject(game), actor_(actor), ctrlKey_(ctrlKey) {
}

ComponentSwitcher::~ComponentSwitcher() {
}

void ComponentSwitcher::update() {
}

void ComponentSwitcher::handleInput(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == ctrlKey_) {
		switchToNext();
	}
}

void ComponentSwitcher::addMode(InputComponent* inputComp,
		PhysicsComponent* physicsComp, RenderComponent* renderComp,
		RenderComponent* modeRendered) {
	inputComps.push_back(inputComp);
	physicsComps.push_back(physicsComp);
	renderActorComps.push_back(renderComp);
	renderIconsComps.push_back(modeRendered);
}

void ComponentSwitcher::setMode(int mode) {
	currentMode = mode;
	actor_->setInputComponent(inputComps[currentMode]);
	actor_->setPhysicsComponent(physicsComps[currentMode]);
	actor_->setRenderComponent(renderActorComps[currentMode]);
}

void ComponentSwitcher::switchToNext() {
	currentMode = (currentMode + 1) % inputComps.size();
	actor_->setInputComponent(inputComps[currentMode]);
	actor_->setPhysicsComponent(physicsComps[currentMode]);
	actor_->setRenderComponent(renderActorComps[currentMode]);
}

void ComponentSwitcher::render() {
	renderIconsComps[currentMode]->render(this);
}