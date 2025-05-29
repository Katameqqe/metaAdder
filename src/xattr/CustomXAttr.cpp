#include "CustomXAttr.hpp"


int CustomXAttr::setcxa(const std::string &filePath, const std::string &name, const std::string &value, int flags)
{
    return setxattr(filePath.c_str(), ("user." + name).c_str(), value.c_str(), value.size(), flags);
}

int CustomXAttr::getcxa(const std::string &filePath, const std::string &name, std::string &value)
{
    value.resize(256);
    ssize_t ret = getxattr(filePath.c_str(), ("user." + name).c_str(), &value[0], value.size());
    if (-1 != ret)
    {
        value.resize(ret);
    }
    return ret;
}

int CustomXAttr::removecxa(const std::string &filePath, const std::string &name)
{
    return removexattr(filePath.c_str(), ("user." + name).c_str());
}

ssize_t CustomXAttr::listcxa(const std::string &filePath, std::vector<std::string> &attr)
{
    ssize_t len = listxattr(filePath.c_str(), nullptr, 0);
    if (len < 0) return len;

    std::vector<char> buffer(len);
    listxattr(filePath.c_str(), buffer.data(), len);
    
    std::string l;
    for (ssize_t i = 0; i < len;)
    {
        l = std::string(&buffer[i]+5);
        attr.push_back(l);
        i += l.size()+6;
    }
    return len;
}