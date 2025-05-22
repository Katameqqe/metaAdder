#include <iostream>
#include <string>
#include <cstring>
#include <sys/xattr.h>
//#include "xattr/class.h"
#include <bitset>

//#include "MetaAdder.hpp"
//
//bool checkFile(const std::string &aPath)
//{
//    bool result = false;
//
//    MetaError::PtrT error = nullptr;
//
//    MetaAdder::PtrT metaAdder = MetaAdder::create(aPath, &error);
//    if (nullptr != metaAdder)
//    {
////        metaAdder->setClassification(aPath, static_cast<char>(MetaProcessor::Type::USER));
//        if (!metaAdder->setClassification("ClassificationValue", &error))
//        {
//            printf("Unable setClassification errorCode: %d\tdecsription: %s",
//                error->errorCode,
//                error->errorDescription.c_str());
//            return false;
//        }
//
//        std::string classification;
//        if (!metaAdder->getClassification(&classification, &error))
//        {
//            printf("Unable getClassification errorCode: %d\tdecsription: %s",
//                error->errorCode,
//                error->errorDescription.c_str());
//            return false;
//        }
//
//        std::cout << "Classification: " << classification << std::endl;
//
//        if (classification == "ClassificationValue")
//        {
//            result = true;
//        }
//        else
//        {
//            // TODO: get and set classification dont match
//        }
//    }
//    else
//    {
//        if (nullptr != error)
//        {
//            printf("Unable to create meta adder: %s", error->errorDescription.c_str());
//        }
//    }
//
//    return result;
//}
//
//void checkAllFiles()
//{
//    printf("Check files:\n");
//
//    // TODO: foreach test file
//    // {
//            if (checkFile("./Test.txt")) // test file path should be here
//            {
//                printf("%s\t\t\t[OK]\n", "./Test.txt"); // test file path
//            }
//            else
//            {
//                printf("%s\t\t\t[FAIL]\n", "./Test.txt"); // test file path
//            }
//    // }
//
//}

int main()
{
    // TODO: make possible to write string to xattr, not single character or flag
    const char *name = "user.class.name";
    const char *value = "worker";
    if (setxattr("./Test.txt", name, value, strlen(value)+1, 0) == -1)
    {
        printf("setxattr fail. Error: %d\t%s", errno, strerror(errno));
        return -2;
    };
    char buff[256];

    if (getxattr("./Test.txt", "user.test", buff, 256) == -1)
    {
        printf("getxattr fail. Error: %d\t%s", errno, strerror(errno));
        return -1;
    };

    std::cout << name << ": " << buff << std::endl;

//    checkFile("./Test.txt");

    //std::cout << _CXA_USER_PREFIX << ": " << std::bitset<8>(buff[0]) << std::endl;

    //checkAllFiles();

    return 0;
}
