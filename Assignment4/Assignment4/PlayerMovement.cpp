
#include "PlayerMovement.h"

PlayerMovement::PlayerMovement() {

}

PlayerMovement::PlayerMovement(const float& speed) {
    componentType = "playerMovement";
    this->speed = speed;
}

PlayerMovement* PlayerMovement::clone() const {
    return new PlayerMovement(*this);
}

void PlayerMovement::SDLInput(const Uint8* k, const float& xRel, const float& yRel) {
    forward = speed * (k[SDL_SCANCODE_W] - k[SDL_SCANCODE_S]);
    right = speed * (k[SDL_SCANCODE_D] - k[SDL_SCANCODE_A]);
    gameObject->GetTransform()->UpdateVelocity(forward, right);

    gameObject->GetTransform()->rotation = glm::vec3(xRel, yRel, 0);
}
