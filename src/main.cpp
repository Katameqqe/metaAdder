#include <iostream>
#include "xattr/CustomXAttr.hpp"
#include "pdfEdit/keyEdit.hpp"
#include "metaAdder/metaWrapper.hpp"

int main()
{
    metaWrapper wrapper("../dd.docx");
    std::string name = "custom.ptr";
    std::string value = "test data";
    if (wrapper.setMeta(name, value) == -1)
    {
        printf("setMeta fail. Error: %d\t%s\n", errno, strerror(errno));
        return -1;
    }
    std::string readData;
    if (wrapper.getMeta(name, readData) == -1)
    {
        printf("getMeta fail. Error: %d\t%s\n", errno, strerror(errno));
        return -1;
    }
    printf("%s: %s\n", name.c_str(), readData.c_str());

    if (wrapper.removeMeta(name) == -1)
    {
        printf("getMeta fail. Error: %d\t%s\n", errno, strerror(errno));
        return -1;
    }
    readData.clear();
    if (wrapper.getMeta(name, readData) == -1)
    {
        printf("getMeta fail. Error: %d\t%s\n", errno, strerror(errno));
        return -1;
    }
    printf("%s: %s\n", name.c_str(), readData.c_str());
    return 0;
}
