#include <iostream>
#include <fstream>
#include <string>
#include "keyEdit.hpp"

int keyEdit::appendAfterEOF(const std::string &filePath, const std::string &data)
{
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);

    if (!file) return -1;

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    const int CHUNK_SIZE = 2048;
    int readSize = std::min<int>(fileSize, CHUNK_SIZE);
    file.seekg(fileSize - readSize, std::ios::beg);

    std::string tail(readSize, '\0');
    file.read(&tail[0], readSize);

    size_t eofPos = tail.rfind("%%EOF");
    if (eofPos == std::string::npos) return -1;

    std::streampos insertPos = fileSize - readSize + eofPos + 6; // 6 = length of '%%EOF' + newline

    file.seekp(insertPos, std::ios::beg);
    file.write(data.c_str(), data.size());

    file.close();

    return static_cast<int>(insertPos);
}

int keyEdit::readAfterEOF(const std::string &filePath, std::string &data)
{
    std::ifstream file(filePath, std::ios::out | std::ios::binary);
    if (!file) return -1;

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    const int CHUNK_SIZE = 2048;
    int readSize = std::min<int>(fileSize, CHUNK_SIZE);
    file.seekg(fileSize - readSize, std::ios::beg);

    std::string tail(readSize, '\0');
    file.read(&tail[0], readSize);

    size_t eofPos = tail.rfind("%%EOF");
    if (eofPos == std::string::npos) return -1;

    data = tail.substr(eofPos + 6); // 6 = length of '%%EOF' + newline
    file.close();

    return static_cast<int>(data.size());
}
