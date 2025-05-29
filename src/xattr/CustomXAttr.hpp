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
    static int setcxa(const std::string &filePath, const std::string &name, const std::string &value, int flags);
    static int getcxa(const std::string &filePath, const std::string &name, std::string &value);
    static int removecxa(const std::string &filePath, const std::string &name);
    static ssize_t listcxa(const std::string &filePath, std::vector<std::string> &attr);
};

#endif