#include <iostream>
#include <string>
#include <cstring>
#include "xattr/class.hpp"
#include <bitset>


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

    std::cout << _CXA_USER_PREFIX << ": " << buff << std::endl;
    return 0;
}
