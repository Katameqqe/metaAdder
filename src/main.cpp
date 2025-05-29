#include <iostream>
#include <string>
#include <cstring>
#include "xattr/CustomXAttr.hpp"
#include <bitset>
#include <memory>
#include "pdfEdit/keyEdit.hpp"


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
    if (CustomXAttr::listcxa("./Test.txt", list) == -1)
    {
        printf("lsitxattr fail. Error: %d\t%s", errno, strerror(errno));
        return -1;
    };

    for (const auto& attr : list) {
        CustomXAttr::getcxa("./Test.txt", attr, buff);
        std::cout << attr << ": "<< "\""<< buff << "\"" << std::endl;
    }

    keyEdit::appendAfterEOF("./spdf.pdf", "custom.ptr","test data");
    keyEdit::appendAfterEOF("./spdf.pdf", "custom.ctr","test");
    keyEdit::removeAfterEOF("./spdf.pdf", "custom.ctr");
    std::string readData;
    keyEdit::readAfterEOF("./spdf.pdf", "custom.ptr", readData);
    
    std::cout << readData << std::endl;
    return 0;
}
