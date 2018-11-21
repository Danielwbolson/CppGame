
#ifndef LOCK_H_
#define LOCK_H_

#include "Component.h"

class Lock : public Component {

private:
    std::string key;

public:
    Lock() {}
    Lock(const std::string&);

};
#endif
