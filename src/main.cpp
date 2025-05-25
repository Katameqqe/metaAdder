#include <iostream>
#include <string>
#include <cstring>
#include "xattr/class.hpp"
#include <bitset>
#include <memory>


int main()
{
    // TODO: make possible to write string to xattr, not single character or flag

    std::string value = "test.classiffier";

    if (CustomXAttr::setcxa("./Test.txt", value, 0) == -1)
    {
        printf("setxattr fail. Error: %d\t%s\n", errno, strerror(errno));
        return -1;
    };
    std::string buff;

    if (CustomXAttr::getcxa("./Test.txt", buff) == -1)
    {
        printf("getxattr fail. Error: %d\t%s", errno, strerror(errno));
        return -1;
    };

    std::string user_prefix = _CXA_USER_PREFIX; 
    if (CustomXAttr::removecxa("./Test.txt", user_prefix) == -1)
    {
        printf("removexattr fail. Error: %d\t%s", errno, strerror(errno));
        return -1;
    };

    std::shared_ptr<char> list = std::shared_ptr<char>(new char[2048]);
    if (CustomXAttr::listcxa("./Test.txt", list.get()) == -1)
    {
        printf("listxattr fail. Error: %d\t%s", errno, strerror(errno));
        return -1;
    };

    std::cout << std::string(list.get()) << std::endl;
    return 0;
}
