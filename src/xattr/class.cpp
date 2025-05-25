#include "class.hpp"

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

int CustomXAttr::removecxa(const char *path, std::string &name)
{
    return removexattr(path, name.c_str());
}

ssize_t CustomXAttr::listcxa(const char *path, char *list)
{
    ssize_t len = listxattr(path, nullptr, 0);
    listxattr(path, list, len);
    int l;
    for (int i = 0; i < len; )
    {
        l = strlen(list);
        list[l] = ' ';
        i = l+1;
    }
    list[len-1] = '\0';
    return len;

}