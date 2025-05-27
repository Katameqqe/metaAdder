#include "CustomXAttr.hpp"


int CustomXAttr::setcxa(const char *path, const std::string &name, std::string &value, int flags)
{
    return setxattr(path, name.c_str(), value.c_str(), value.size(), flags);
}

int CustomXAttr::getcxa(const char *path, const std::string &name, std::string &value)
{
    value.resize(256);
    ssize_t ret = getxattr(path, name.c_str(), &value[0], value.size());
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

ssize_t CustomXAttr::listcxa(const char *path, std::vector<std::string> &attr)
{
    ssize_t len = listxattr(path, nullptr, 0);
    if (len < 0) return len;

    std::vector<char> buffer(len);
    listxattr(path, buffer.data(), len);
    
    std::string l;
    for (ssize_t i = 0; i < len;)
    {
        l = std::string(&buffer[i]);
        attr.push_back(l);
        i += l.size() + 1;
    }
    return len;
}