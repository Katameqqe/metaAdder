#include <iostream>
#include <string>
#include <cstring>
#include <sys/xattr.h>
//#include "xattr/class.h"
#include <bitset>

#include "MetaAdder.hpp"

bool checkFile(const std::string &aPath)
{
    bool result = false;

    MetaAdder::PtrT metaAdder = MetaAdder::create(aPath);
    if (nullptr != metaAdder)
    {
        metaAdder->setClassification(aPath, static_cast<char>(MetaProcessor::Type::USER));
        std::string classification = metaAdder->getClassification();

        std::cout << "Classification: " << classification << std::endl;

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
    checkFile("./Test.txt");

    //std::cout << _CXA_USER_PREFIX << ": " << std::bitset<8>(buff[0]) << std::endl;

    //checkAllFiles();

    return 0;
}
