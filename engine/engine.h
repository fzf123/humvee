#pragma once

namespace humvee {

class Engine {
public:
    Engine() {}
    virtual ~Engine() {}
    virtual int init() = 0;
    virtual int run() = 0;
};

}
