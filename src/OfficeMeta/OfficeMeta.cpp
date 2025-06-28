#include "OfficeMeta.hpp"

int OfficeMeta::setProp(const std::string &filePath, const std::string &name, const std::string &value)
{
    int err = 0;
    zip_t *za = zip_open(filePath.c_str(), 0, &err);
    if (!za)
    {
        return err;
    }
    
    if (zip_name_locate(za, "docProps/custom.xml", 0) == -1)
    {
        zip_file_t *zf;
        zip_source_t *zs;
        zf = zip_fopen(za, "[Content_Types].xml",0);
        std::vector<char> buff(4096);
        std::string cont_content;
        zip_int64_t n;
        while ((n = zip_fread(zf, buff.data(), buff.size())) > 0) {
            cont_content.append(buff.data(), n);
        }
        zip_int64_t pos = cont_content.rfind("</Types>");
        cont_content.insert(pos,"<Override PartName=\"/docProps/custom.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.custom-properties+xml\"/>");
        zip_fclose(zf);
        zs = zip_source_buffer(za, cont_content.c_str(), cont_content.length(), 0);

        if (!zs)
        {
            printf("ZS error");
            zip_close(za);
            return -1;
        }
        if (zip_file_add(za, "[Content_Types].xml", zs, ZIP_FL_ENC_UTF_8 | ZIP_FL_OVERWRITE) < 0)
        {
            zip_source_free(zs);
            printf("ZS add error: %s\n", zip_strerror(za));
            printf("Error code: %d\n", zip_error_code_zip(zip_get_error(za)));
            zip_close(za);
            return -1;
        }
        printf("%s\n",cont_content.c_str());

        std::string custom_content = std::string("<Properties xmlns=\"http://schemas.openxmlformats.org/officeDocument/2006/custom-properties\" xmlns:vt=\"http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes\">\r\n<property fmtid=\"{D5CDD505-2E9C-101B-9397-08002B2CF9AE}\" pid=\"2\" name=\"") + name + std::string("\"><vt:lpwstr>") + value + std::string("</vt:lpwstr></property></Properties>");
        //printf("%s\n", custom_content.c_str());
        zs = zip_source_buffer(za, custom_content.c_str(), custom_content.size(), 0);
        if (!zs)
        {
            printf("Zcustom error");
            zip_close(za);
            return -1;
        }
        if (zip_file_add(za, "docProps/custom.xml", zs, ZIP_FL_OVERWRITE | ZIP_FL_ENC_UTF_8) < 0)
        {
            zip_source_free(zs);
            printf("Zcustom add error");
            zip_close(za);
            return -1;
        }
    }
    else
    {
        std::string content;
        zip_file_t *zf = zip_fopen(za, "[Content_Types]", 0);
        std::vector<char> buf(4096);

        zip_int64_t n;
        while ((n = zip_fread(zf, buf.data(), buf.size())) > 0) {
            content.append(buf.data(), n);
        }
        zip_fclose(zf);

        std::string fstr = std::string("name=\"")+name+std::string("\">");
        const std::string fvp = "<vt:lpwstr>";
        const std::string lvp = "</vt:lpwstr>";

        std::size_t indx = content.rfind(fstr.c_str());
        if (indx == std::string::npos)
        {
            indx = content.rfind("<property ");
            indx += 62;
            int size_n = content.find("\"",indx) - indx;
            int next_n = std::stoi(content.substr(indx, size_n))+1;

            std::string result = std::string("<property fmtid=\"{D5CDD505-2E9C-101B-9397-08002B2CF9AE}\" pid=\"")+std::to_string(next_n)+std::string("\" name=\"")+name+std::string("\"><vt:lpwstr>")+value+std::string("</vt:lpwstr></property>");
            indx = content.rfind("</Properties>");
            content.insert(indx, result);
        }
        else
        {
            indx += fstr.size()+fvp.size();
            std::size_t n = content.find(lvp, indx) - indx;
            content.erase(indx, n);
            content.insert(indx, value);
        }

        zip_source_t *zs = zip_source_buffer(za, content.c_str(), content.size(), 0);
        zip_file_add(za, "docProps/custom.xml", zs, ZIP_FL_OVERWRITE | ZIP_FL_ENC_UTF_8);

        zip_source_close(zs);
    }

    
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
    else 
    {
        if (zip_name_locate(za, "docProps/custom.xml", 0) == -1) return -1;
        zip_file_t *zf = zip_fopen(za, "docProps/custom.xml", 0);
        
        std::vector<char> buf(4096);
        std::string content;
        zip_int64_t n;
        while ((n = zip_fread(zf, buf.data(), buf.size())) > 0) {
            content.append(buf.data(), n);
        }
        printf("%s\n",content.c_str());
        zip_fclose(zf);
        zip_close(za);
        return -1;
        std::string fstr = std::string("name=\"")+name+std::string("\">");
        const std::string fvp = "<vt:lpwstr>";
        const std::string lvp = "</vt:lpwstr>";
        std::size_t indx = content.rfind(fstr.c_str());
        if (indx != std::string::npos)
        {
            indx += fstr.size() + fvp.size();
            std::size_t n = content.find(lvp.c_str(),indx) - indx;
            value = content.substr(indx, n);
        }
        else
        {
            zip_close(za);
            return 0;
        }
    };
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

    zip_file_t *zf = zip_fopen(za, "docProps/custom.xml", 0);

    std::vector<char> buf(4096);
    std::string content;
    zip_int64_t n;
    while ((n = zip_fread(zf, buf.data(), buf.size())) > 0) {
        content.append(buf.data());
    }
    zip_fclose(zf);
    std::string fstr = std::string("name=\"")+name+std::string("\">");
    std::size_t indx = content.rfind(fstr.c_str());
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