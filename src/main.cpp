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

    if (CustomXAttr::setcxa("./Test.txt", _CXA_USER_PREFIX, value, 0) == -1)
    {
        printf("setxattr fail. Error: %d\t%s\n", errno, strerror(errno));
        return -1;
    };
    std::string buff;

    if (CustomXAttr::getcxa("./Test.txt", _CXA_USER_PREFIX, buff) == -1)
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

    std::vector<std::string> list;
    list = CustomXAttr::listcxa("./Test.txt");

    for (const auto& attr : list) {
        CustomXAttr::getcxa("./Test.txt", attr, buff);
        std::cout << attr << ": "<< "\""<< buff << "\"" << std::endl;
    }
    return 0;
}
