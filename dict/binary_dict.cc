#include "binary_dict.h"

#include <fcntl.h> // open
#include <sys/mman.h> // mmap
#include <sys/stat.h> // fstat
#include <unistd.h> // close

namespace humvee {

BinaryDict::BinaryDict() {
}

BinaryDict::~BinaryDict() {
}

static int read_int(int& offset, const char* buf, int& ret) {
    ret = *((int*)(buf + offset));
    offset += 4;
    return 0;
}

static int read_string(int& offset, const char* buf, int len, std::string& ret) {
    ret = std::string(buf + offset, buf + offset + len);
    offset += len;
    return 0;
}

int BinaryDict::load() {
    int fd = open(_dict_file.c_str(), O_RDONLY);
    if (fd < 0) {
        return -1;
    }

    struct stat sbuf;
    if (fstat(fd, &sbuf) < 0) {
        close(fd);
        return -2;
    }

    int buf_size = sbuf.st_size;
    char* src = (char*)mmap(0, buf_size, PROT_READ, MAP_SHARED, fd, 0);
    if (src == MAP_FAILED) {
        close(fd);
        return -3;
    }
    
    int offset = 0;
    while (offset < buf_size) {
        int key_len = 0;
        int val_len = 0;
        std::string key;
        std::string val;

        read_int(offset, src, key_len);
        read_string(offset, src, key_len, key);
        read_int(offset, src, val_len);
        read_string(offset, src, val_len, val);
    }
    munmap((void*)src, buf_size);
    close(fd);
    return 0;
}

}
