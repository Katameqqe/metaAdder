#pragma once

#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>


class keyEdit
{
public: 
    static int appendAfterEOF(const std::string &filePath, const std::string &name, const std::string &value);
    static int readAfterEOF(const std::string &filePath, const std::string &name ,std::string &data);
private:
    static void truncate(const std::string &filePath, std::streampos pos)
    {
        #if defined(_WIN32)
            #include <io.h>
            int fd = _open(filePath.c_str(), _O_RDWR);
            _chsize_s(fd, pos);
            _close(fd);
        #elif defined(__APPLE__) || defined(__linux__)
            #include <unistd.h>
            int fd = open(filePath.c_str(), O_WRONLY);
            ftruncate(fd, pos);
            close(fd);
        #endif
    }
};