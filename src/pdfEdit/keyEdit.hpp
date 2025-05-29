#pragma once

#include <fstream>
#include <string>

#if defined(_WIN32)
    #include <io.h>
    #include <fcntl.h>
#elif defined(__APPLE__) || defined(__linux__)
    #include <unistd.h>
    #include <fcntl.h>
#endif

class keyEdit
{
public: 
    static int appendAfterEOF(const std::string &filePath, const std::string &name, const std::string &value);
    static int readAfterEOF(const std::string &filePath, const std::string &name ,std::string &data);
    static int removeAfterEOF(const std::string &filePath, const std::string &name);

private:
    static void truncate(const std::string &filePath, std::streampos pos)
    {
        #if defined(_WIN32)
            int fd = _open(filePath.c_str(), _O_RDWR);
            _chsize_s(fd, static_cast<__int64>(pos));
            _close(fd);
        #elif defined(__APPLE__) || defined(__linux__)
            int fd = open(filePath.c_str(), O_WRONLY);
            ftruncate(fd, static_cast<off_t>(pos));
            close(fd);
        #endif
    }
};