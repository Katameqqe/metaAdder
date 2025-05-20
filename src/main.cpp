#include <iostream>
#include <string>
#include <cstring>
#include <sys/xattr.h>
#include "xattr/class.h"
#include <bitset>

int main()
{
    if (setcxa("./Test.txt", CXA_TRUSTED, 0) == -1)
    {
        std::cout << "Error setting xattr" << std::endl;
        return -1;
    };
    char buff[1];

    if (getcxa("./Test.txt", buff) == -1)
    {
        std::cout << "Error getting xattr" << std::endl;
        return -1;
    };

    std::cout << _CXA_USER_PREFIX << ": " << std::bitset<8>(buff[0]) << std::endl;

    return 0;
}
