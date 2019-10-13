
#include "Grab.h"

Grab::Grab() {
    componentType = "grab";
}

Grab* Grab::clone() const {
    return new Grab(*this);
}

void Grab::Update(const float& dt) {
    Collider* c = (Collider*)gameObject->GetComponent("collider");
    if (c && c->colliding) {
        InteractableObject* io = (InteractableObject*)c->colliderObj->GetComponent("interactableObject");

        if (io && !isHolding) {
            GrabObject(io->gameObject);
            Collider* otherCol = (Collider*)io->gameObject->GetComponent("collider");
            otherCol->dynamic = true;
        }
    }

    if (grabbedObj && !grabbedObj->dead) {
        grabbedObj->GetTransform()->UpdateVelocity(
            gameObject->GetTransform()->velocity.x, gameObject->GetTransform()->velocity.z);

        grabbedObj->GetTransform()->UpdatePosition(
            gameObject->GetTransform()->position + 2.0f * gameObject->GetTransform()->forward);

        grabbedObj->GetTransform()->forward = gameObject->GetTransform()->forward;
    }
    else {
        isHolding = false;
        grabbedObj = nullptr;
    }
}

void Grab::GrabObject(GameObject* c) {
    isHolding = true;
    grabbedObj = c;

    grabbedObj->GetTransform()->UpdatePosition(
        gameObject->GetTransform()->position + 2.0f * gameObject->GetTransform()->forward);
    grabbedObj->GetTransform()->forward = gameObject->GetTransform()->forward;
}