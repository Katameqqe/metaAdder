#include "class.hpp"

#ifdef _SYS_XATTR_H
int CustomXAttr::setcxa(const char *path, std::string value, int flags)
{
    return setxattr(path, _CXA_USER_PREFIX, value.c_str(), value.size(), flags);
}

int CustomXAttr::getcxa(const char *path, std::string &value)
{
    value.resize(256);
    ssize_t ret = getxattr(path, _CXA_USER_PREFIX, &value[0], value.size());
    if (-1 != ret)
    {
        value.resize(ret);
    }
    return ret;
}
#endif

#ifdef _SYS_XATTR_H_
int CustomXAttr::setcxa(const char *path, std::string value, int pos, int flags)
{
    return setxattr(path, _CXA_USER_PREFIX, value.c_str(), value.size(), pos, flags);
}
int CustomXAttr::getcxa(const char *path, std::string &value, int pos, int flags)
{
    value.resize(256);
    ssize_t ret = getxattr(path, _CXA_USER_PREFIX, &value[0], value.size(), pos, flags);
    if (-1 != ret)
    {
        value.resize(ret);
    }
    return ret;
}
#endif