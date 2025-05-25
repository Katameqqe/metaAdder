#ifndef _CUSTOM_XATTR_H
#define _CUSTOM_XATTR_H

#include <string>
#include <cstring>
#include <sys/xattr.h>
#include <vector>

#define _CXA_USER_PREFIX  "user.classifier"


class CustomXAttr
{
public:
    static int setcxa(const char *path, const std::string &name, std::string &value, int flags);
    static int getcxa(const char *path, const std::string &name, std::string &value);
    static int removecxa(const char *path, std::string &name);
    static std::vector<std::string> listcxa(const char *path);
};

#endif