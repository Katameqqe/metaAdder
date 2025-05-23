#ifndef _CUSTOM_XATTR_H
#define _CUSTOM_XATTR_H

#include <string>
#include <cstring>
#include <sys/xattr.h>

#define _CXA_USER_PREFIX  "user.classifier"


class CustomXAttr
{
public:
    #ifdef _SYS_XATTR_H
    static int setcxa(const char *path, std::string value, int flags);
    static int getcxa(const char *path, std::string &value);
    //int removecxa(const char *path, const char *name);
    //ssize_t listcxa(const char *path, char *list, size_t size);
    #endif
    #ifdef _SYS_XATTR_H_
    static int setcxa(const char *path, std::string value, int pos,int flags);
    static int getcxa(const char *path, std::string &value, int pos, int flags);
    #endif
};

#endif