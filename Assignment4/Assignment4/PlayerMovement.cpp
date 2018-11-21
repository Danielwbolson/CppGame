
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

void PlayerMovement::SDLInput(const Uint8* k) {
    forward = speed * (k[SDL_SCANCODE_W] - k[SDL_SCANCODE_S]);
    right = speed * (k[SDL_SCANCODE_D] - k[SDL_SCANCODE_A]);
    gameObject->GetTransform()->UpdateVelocity(forward, right);
    if (forward > 0 || right > 0) {
        int test = 1;
    }
}
