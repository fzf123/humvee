#pragma once

#include <string>
#include <vector>

namespace humvee {

class BinaryDictDumper {
public:
    BinaryDictDumper();
    virtual ~BinaryDictDumper();

    void add(const std::string& key, const std::string& val);
    int dump(const char* file_name);

private:
    std::vector<std::pair<std::string, std::string> > _kv_vec;
};

}
