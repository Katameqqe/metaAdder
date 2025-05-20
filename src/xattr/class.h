#ifndef _CUSTOM_XATTR_H
#define _CUSTOM_XATTR_H

#include <string>
#include <cstring>
#include <sys/xattr.h>

constexpr char CXA_USER     =  0b00000001;
constexpr char CXA_SYSTEM   =  0b00000010;
constexpr char CXA_SECURITY =  0b00000100;
constexpr char CXA_TRUSTED  =  0b00001000;
constexpr char CXA_OTHER    =  0b00000000;

#define _CXA_USER_PREFIX  "user.classifier"

extern "C++" {
    int setcxa(const char *path, const char value, int flags);
    int getcxa(const char *path, char *value);
    //int removecxa(const char *path, const char *name);
    //ssize_t listcxa(const char *path, char *list, size_t size);
}

#endif