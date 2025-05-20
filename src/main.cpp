#include <iostream>
#include <string>
#include <cstring>
#include <sys/xattr.h>

#include "MetaAdder.hpp"

bool checkFile(const std::string &aPath)
{
    bool result = false;

    MetaAdder::PtrT metaAdder = MetaAdder::create(aPath);
    if (nullptr != metaAdder)
    {
        metaAdder->setClassification("MyClassification");
        std::string classification = metaAdder->getClassification();

        if (classification == "MyClassification")
        {
            result = false;
        }
    }

    return result;
}

void checkAllFiles()
{
    printf("Check files:\n");

    // TODO: foreach test files
    // {
            if (checkFile("./Test.txt")) // test file path should be here
            {
                printf("%s\t\t\t[OK]\n", "./Test.txt"); // test file path
            }
            else
            {
                printf("%s\t\t\t[FAIL]\n", "./Test.txt"); // test file path
            }
    // }

}

int main()
{
    const char *name = "user.class.name";
    const char *value = "worker";
    if (setxattr("./Test.txt", name, value, strlen(value)+1, 0, 0))
    {
        return -2;
    };
    char buff[256];

    if (getxattr("./Test.txt", "user.test", buff, 256, 0, 0) == -1)
    {
        return -1;
    };

    std::cout << name << ": " << buff << std::endl;

    checkAllFiles();

    return 0;
}
