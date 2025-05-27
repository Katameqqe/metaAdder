#include <fstream>
#include <string>

class keyEdit
{
public: 
    static int appendAfterEOF(const std::string &filePath, const std::string &data);
    static int readAfterEOF(const std::string &filePath, std::string &data);
};