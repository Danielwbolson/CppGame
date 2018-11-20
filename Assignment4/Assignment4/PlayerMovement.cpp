
#include "PlayerMovement.h"

PlayerMovement::PlayerMovement() {
    componentType = "playerMovement";
}

PlayerMovement::PlayerMovement(const float& speed) {
    this->speed = speed;
}

PlayerMovement* PlayerMovement::clone() const {
    return new PlayerMovement(*this);
}

void PlayerMovement::Update(const float& dt) {

}