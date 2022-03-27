//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    auto physicsComp = this->gameObject->getComponent<PhysicsComponent>();
    physicsComp->setLinearVelocity(glm::vec2(2, 0));
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
        std::cout << "some key pressed" << std::endl;
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            auto physicsComp = this->gameObject->getComponent<PhysicsComponent>();
            physicsComp->setLinearVelocity(glm::vec2(2, 0));
            physicsComp->addForce(glm::vec2(0, 6));
        }
    } else if (event.type == SDL_KEYUP){
        std::cout << "some key released" << std::endl;
    }

    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
    std::string name = comp->getGameObject()->name;

    if (name == "Coin")
    {
        comp->getGameObject()->shouldBeDeleted = true;
    }
    else {
        BirdGame::instance->setGameState(GameState::GameOver);
        std::cout << "bird collided with something" << std::endl;
    }


}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}



