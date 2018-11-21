
#ifndef CAMERA_H_
#define CAMERA_H_

#define GLM_FORCE_RADIANS //ensure we are using radians
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Vec3.h"
#include "Component.h"
#include "Transform.h"

#include <stdio.h>

class Camera : public Component {

private:

public:
    Camera();
    Camera(const Vec3&, const Vec3&, 
        const int&, const int&, const float&, const float&, const float&);
    Camera* clone() const;

    void Update(const float&);

    Camera operator=(const Camera&);

    glm::mat4 view;
    glm::mat4 proj;

    glm::vec3 lookAt;
    glm::vec3 up;

    float fov, aspect_ratio;
    float near_plane, far_plane;
};

#endif