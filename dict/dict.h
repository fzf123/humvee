#pragma once

#include <string>

namespace humvee {

class Dict {
public:
    Dict() {}
    virtual ~Dict() {}

    virtual int load() = 0;

    const std::string& get_dict_file() const {
        return _dict_file;
    }

protected:
    std::string _dict_file;
};

}
