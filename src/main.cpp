#include <iostream>
#include <dirent.h>
#include "xattr/CustomXAttr.hpp"
#include "pdfEdit/keyEdit.hpp"
#include "metaAdder/metaWrapper.hpp"

std::vector<std::string> listFiles(const std::string& dir) {
    std::vector<std::string> files;
    DIR* dp = opendir(dir.c_str());
    if (!dp) return files;
    struct dirent* entry;
    while ((entry = readdir(dp)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;
        files.push_back(dir + "/" + name);
    }
    closedir(dp);
    return files;
}

int TestFile(std::string Path)
{
    metaWrapper wrapper(Path);
    const std::string name = "custom.ptr";
    const std::string value = "test data";
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

int main(int argc, const char** argv) {
    std::vector<std::string> files;
    if (argc <= 1)
    {
        files = listFiles("../files");
    }
    else
    {
        files = listFiles(argv[1]);
    }
    for (const auto& f : files) {
        printf("\nFile: %s\n", f.c_str());
        TestFile(f);
    }
    return 0;
}
