#include <iostream>
#include <string>
#include <cstring>
#include <sys/xattr.h>
#include "xattr/class.h"
#include <bitset>

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
            result = true;
        }
    }

    return result;
}

void checkAllFiles()
{
    printf("Check files:\n");

    // TODO: foreach test file
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

    checkAllFiles();

    return 0;
}
