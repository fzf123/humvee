#pragma once

#include "dict.h"

namespace humvee {

class BinaryDict : public Dict {
public:
    BinaryDict();
    virtual ~BinaryDict();

    int load() override;
};

}
