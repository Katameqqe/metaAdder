#include "OfficeMeta.hpp"

int OfficeMeta::setProp(const std::string &filePath, const std::string &name, const std::string &value)
{
    int err = 0;
    zip_t *za = zip_open(filePath.c_str(), 0, &err);
    if (!za)
    {
        return err;
    }
    std::string content;

    zip_file_t *zf = zip_fopen(za, "docProps/app.xml", 0);
    std::vector<char> buf(4096);

    zip_int64_t n;
    while ((n = zip_fread(zf, buf.data(), buf.size())) > 0) {
        content.append(buf.data());
    }
    zip_fclose(zf);

    const std::string fprop = (std::string("<") + name + std::string(">"));
    const std::string lprop = (std::string("</") + name + std::string(">"));

    std::size_t indx = content.rfind(fprop.c_str());
    if (indx == std::string::npos)
    {
        indx = content.rfind("</Properties>");
        std::string result = fprop + value + lprop;
        content.insert(indx, result);
    }
    else
    {
        indx += name.size()+2;
        std::size_t n = content.rfind(lprop) - indx;
        content.erase(indx, n);
        content.insert(indx, value);
    }

    zip_source_t *zs = zip_source_buffer(za, content.c_str(), content.size(), 0);
    zip_file_add(za, "docProps/app.xml", zs, ZIP_FL_OVERWRITE | ZIP_FL_ENC_UTF_8);
    
    zip_source_close(zs);
    zip_close(za);
    
    return 0;
}
int OfficeMeta::getProp(const std::string &filePath, const std::string &name, std::string &value)
{
    int err = 0;
    zip_t *za = zip_open(filePath.c_str(), 0, &err);
    if (!za)
    {
        return err;
    }

    zip_file_t *zf = zip_fopen(za, "docProps/app.xml", 0);
    std::vector<char> buf(4096);
    std::string content;
    zip_int64_t n;
    while ((n = zip_fread(zf, buf.data(), buf.size())) > 0) {
        content.append(buf.data());
    }
    zip_fclose(zf);

    std::size_t indx = content.rfind((std::string("<") + name + std::string(">")).c_str());
    if (indx != std::string::npos)
    {
        indx += name.size()+2;
        std::size_t n = content.rfind((std::string("</") + name + std::string(">")).c_str()) - indx;
        value = content.substr(indx, n);
    }
    else
    {
        zip_close(za);
        return 0;
    }
    zip_close(za);
    return 0;
}
int OfficeMeta::rmProp(const std::string &filePath, const std::string &name)
{
    int err = 0;
    zip_t *za = zip_open(filePath.c_str(), 0, &err);
    if (!za)
    {
        return err;
    }

    zip_file_t *zf = zip_fopen(za, "docProps/app.xml", 0);
    std::vector<char> buf(4096);
    std::string content;
    zip_int64_t n;
    while ((n = zip_fread(zf, buf.data(), buf.size())) > 0) {
        content.append(buf.data());
    }
    zip_fclose(zf);

    std::size_t indx = content.rfind((std::string("<") + name + std::string(">")).c_str());
    if (indx != std::string::npos)
    {
        std::size_t n = (content.rfind((std::string("</") + name + std::string(">")).c_str()) + name.size() + 2 ) - indx;
        content.erase(indx, n);
        
        zip_source_t *zs = zip_source_buffer(za, content.c_str(), content.size(), 0);
        zip_file_add(za, "docProps/app.xml", zs, ZIP_FL_OVERWRITE | ZIP_FL_ENC_UTF_8);
        
        zip_source_close(zs);
    }

    
    zip_close(za);
    return 0;

}