#include <iostream>
#include <string>
#include <cstring>
#include <sys/xattr.h>

int main()
{
    const char *name = "user.class.name";
    const char *value = "worker";
    if (setxattr("./Test.txt", name, value, strlen(value)+1, 0))
    {
        return -2;
    };
    char buff[256];

    if (getxattr("./Test.txt", "user.test", buff, 256) == -1)
    {
        return -1;
    };

    std::cout << name << ": " << buff << std::endl;

    return 0;
}
