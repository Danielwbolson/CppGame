
#include "Lock.h"

Lock::Lock(const std::string& k) {
    key = k;
}

void Lock::UnLock(const std::string& k) {
    if (k == key)
        gameObject->GetTransform()->velocity += glm::vec3(0, -0.1f, 0);
}