
#ifndef LOCK_H_
#define LOCK_H_

#include "Component.h"
#include "Transform.h"

class Lock : public Component {

private:
    std::string key;

public:
    Lock() {}
    Lock(const std::string&);

    void UnLock(const std::string&);
    std::string GetKey() const { return key; }

};
#endif
