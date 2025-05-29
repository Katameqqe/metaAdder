#include "keyEdit.hpp"

int keyEdit::appendAfterEOF(const std::string &filePath, const std::string &name, const std::string &value)
{
    std::ifstream file(filePath, std::ios::binary);

    if (!file) return -1;

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    const std::streampos CHUNK_SIZE = 2048;
    std::streampos readSize = std::min<std::streampos>(fileSize, CHUNK_SIZE);
    file.seekg(fileSize - readSize, std::ios::beg);

    std::string tail(readSize, '\0');
    file.read(&tail[0], readSize);
    file.close();

    std::size_t eofPos = tail.rfind("\" \\cpdf>");
    if (eofPos == std::string::npos)
    {
        eofPos = tail.rfind("%%EOF");
        if (eofPos == std::string::npos)
        {
            return -1;
        }
        eofPos += 6;
    }
    else 
    {
        eofPos += 9;
    }
    std::string nameStr = ("<cpdf name=\"" + name + "\"");
    std::size_t namePos = tail.find(nameStr);
    std::string *buff = nullptr;
    if (namePos != std::string::npos)
    {
        std::size_t nameEndPos = tail.find("\\cpdf>\n",namePos) + 8;
        if (nameEndPos <= tail.size())
        {
            buff = new std::string(tail.substr(static_cast<std::size_t>(nameEndPos-1)));
        }
        eofPos = namePos;
    }
    std::streampos insertPos = fileSize - readSize + eofPos;
    std::string writeData = "<cpdf name=\"" + name + "\" value=\"" + value + "\" \\cpdf>\n";
    std::fstream wfile(filePath, std::ios::in | std::ios::out | std::ios::binary);
    wfile.seekp(insertPos, std::ios::beg);
    wfile.write(writeData.c_str(), writeData.size());
    if (buff != nullptr)
    {
        wfile.write(buff->c_str(), buff->size());
        delete buff;
    }
    wfile.flush();
    std::streampos newSize = wfile.tellp();
    wfile.close();
    if (newSize < fileSize)
    {
        keyEdit::truncate(filePath, newSize);
    }

    return static_cast<int>(insertPos);
}

int keyEdit::readAfterEOF(const std::string &filePath, const std::string &name, std::string &value)
{
    std::ifstream file(filePath, std::ios::out | std::ios::binary);
    if (!file) return -1;

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    const std::streampos CHUNK_SIZE = 2048;
    std::streampos readSize = std::min<std::streampos>(fileSize, CHUNK_SIZE);
    file.seekg(fileSize - readSize, std::ios::beg);

    std::string tail(readSize, '\0');
    file.read(&tail[0], readSize);

    size_t cpdfPos = tail.rfind("<cpdf name=\"" + name + "\"");
    if (cpdfPos == std::string::npos) return -1;
    cpdfPos += (std::string("<cpdf name=\"") + name + std::string("\" value=\"")).size();
    value = tail.substr(cpdfPos, tail.find("\" \\cpdf>", cpdfPos)-cpdfPos);
    file.close();

    return 0;
}

int keyEdit::removeAfterEOF(const std::string &filePath, const std::string &name)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return -1;

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    const std::streampos CHUNK_SIZE = 2048;
    std::streampos readSize = std::min<std::streampos>(fileSize, CHUNK_SIZE);
    file.seekg(fileSize - readSize, std::ios::beg);

    std::string tail(readSize, '\0');
    file.read(&tail[0], readSize);
    file.close();

    size_t cpdfPos = tail.rfind("<cpdf name=\"" + name + "\"");
    if (cpdfPos == std::string::npos) return -1;

    size_t endPos = tail.find("\\cpdf>\n", cpdfPos) + 8;
    if (endPos == std::string::npos) return -1;

    tail.erase(cpdfPos, endPos - cpdfPos);

    std::fstream wfile(filePath, std::ios::in | std::ios::out | std::ios::binary);
    wfile.seekp(fileSize - readSize, std::ios::beg);
    wfile.write(tail.c_str(), tail.size());
    wfile.flush();
    
    std::streampos newSize = wfile.tellp();
    wfile.close();
    
    if (newSize < fileSize)
    {
        keyEdit::truncate(filePath, newSize);
    }

    return 0;
}

int keyEdit::listAfterEOF(const std::string &filePath, std::vector<std::string> &list)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return -1;

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    const std::streampos CHUNK_SIZE = 2048;
    std::streampos readSize = std::min<std::streampos>(fileSize, CHUNK_SIZE);
    file.seekg(fileSize - readSize, std::ios::beg);

    std::string tail(readSize, '\0');
    file.read(&tail[0], readSize);
    file.close();

    size_t pos = 0;
    while ((pos = tail.find("<cpdf name=\"", pos)) != std::string::npos)
    {
        size_t endPos = tail.find("\"", pos + 12);
        if (endPos == std::string::npos) break;
        list.push_back(tail.substr(pos + 12, endPos - pos - 12));
        pos = endPos + 1;
    }

    return 0;
}