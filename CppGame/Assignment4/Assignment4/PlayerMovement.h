
#ifndef PLAYER_MOVEMENT_H_
#define PLAYER_MOVEMENT_H_

#include "Component.h"
#include "Transform.h"

class PlayerMovement : public Component {

private:
    float speed;
    float forward, right;

public:
    PlayerMovement();
    PlayerMovement(const float&);
    PlayerMovement* clone() const;

    void SDLInput(const Uint8*, const float&, const float&);
};

#endif
