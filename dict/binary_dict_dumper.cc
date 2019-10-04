#include "binary_dict_dumper.h"

#include <cstring>
#include <fcntl.h> // open
#include <sys/mman.h> // mmap
#include <unistd.h> // close

namespace humvee {

static int write_int(int& offset, char* buf, int val) {
    int* ptr = (int*)(buf + offset);
    *ptr = val;
    offset += sizeof(int);
    return 0;
}

static int write_string(int& offset, char* buf, const std::string& val) {
    memcpy(buf + offset, val.c_str(), val.length());
    offset += val.length();
    return 0;
}

BinaryDictDumper::BinaryDictDumper() {
}

BinaryDictDumper::~BinaryDictDumper() {
}

void BinaryDictDumper::add(const std::string& key, const std::string& val) {
    _kv_vec.push_back(std::make_pair(key, val));
}

int BinaryDictDumper::dump(const char* file_name) {
    int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        return -1;
    }

    off_t fsz = 0;
    for (const auto& kv : _kv_vec) {
        int offset = 0;
        int key_len = kv.first.length();
        int val_len = kv.second.length();
        int total_len = sizeof(int) * 2 + key_len + val_len;
        char* dst = (char*)mmap(0, total_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, fsz);
        if (dst == MAP_FAILED) {
            close(fd);
            return -2;
        }

        write_int(offset, dst, key_len);
        write_string(offset, dst, kv.first);
        write_int(offset, dst, val_len);
        write_string(offset, dst, kv.second);

        fsz += total_len;
    }
    close(fd);
    return 0;
}

}
