#include "OfficeMeta.hpp"

int OfficeMeta::setProp(const std::string &filePath, const std::string &name, const std::string &value, MetaLogger &logger)
{
    logger.log("[OfficeMeta] Opening zip file");
    int err = 0;
    zip_t *za = zip_open(filePath.c_str(), 0, &err);
    if (!za)
    {
        return err;
    }

    std::string content;
    std::size_t indx;
    logger.log("[OfficeMeta] Finding docProps/custom.xml");
    if (zip_name_locate(za, "docProps/custom.xml", 0) == -1)
    {
        logger.log("[OfficeMeta] Not Found docProps/custom.xml");
        logger.log("[OfficeMeta] Editing [Content_Types].xml");
        writeToStr(za, "[Content_Types].xml", content);
        
        zip_source_t *zs;
        zip_int64_t indx = content.rfind("</Types>");
        content.insert(indx,"<Override PartName=\"/docProps/custom.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.custom-properties+xml\"/>");
        zs = zip_source_buffer(za, content.c_str(), content.length(), 0);

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
        logger.log("[OfficeMeta] Succesfully edited [Content_Types].xml");
        logger.log("[OfficeMeta] Creating docProps/custom.xml");
        content.clear();
        content = "<Properties xmlns=\"http://schemas.openxmlformats.org/officeDocument/2006/custom-properties\" xmlns:vt=\"http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes\">\r\n<property fmtid=\"{D5CDD505-2E9C-101B-9397-08002B2CF9AE}\" pid=\"2\" name=\"" + name + "\"><vt:lpwstr>" + value + "</vt:lpwstr></property></Properties>";
        zs = zip_source_buffer(za, content.c_str(), content.size(), 0);
        if (!zs)
        {
            printf("Zsource error");
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
        logger.log("[OfficeMeta] Found docProps/custom.xml");
        writeToStr(za, "docProps/custom.xml", content);

        const std::string fstr = "name=\"" + name + "\">";
        const std::string fvp = "<vt:lpwstr>";
        const std::string lvp = "</vt:lpwstr>";

        std::size_t indx = content.rfind(fstr.c_str());
        if (indx == std::string::npos)
        {
            logger.log("[OfficeMeta] Adding custom propery to file");
            indx = content.rfind("<property ");
            indx += 62;
            int size_n = content.find("\"",indx) - indx;
            int next_n = std::stoi(content.substr(indx, size_n))+1;

            std::string result = "<property fmtid=\"{D5CDD505-2E9C-101B-9397-08002B2CF9AE}\" pid=\""+std::to_string(next_n)+"\" name=\""+name+"\"><vt:lpwstr>"+value+"</vt:lpwstr></property>";
            indx = content.rfind("</Properties>");
            content.insert(indx, result);
        }
        else
        {
            logger.log("[OfficeMeta] Propery is found replacing old");
            indx += fstr.size()+fvp.size();
            std::size_t n = content.find(lvp, indx) - indx;
            content.erase(indx, n);
            content.insert(indx, value);
        }

        zip_source_t *zs = zip_source_buffer(za, content.c_str(), content.size(), 0);
        if (!zs)
        {
            printf("Zsource error");
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
        zip_source_close(zs);
    }
    logger.log("[OfficeMeta] Succesfully edited docProps/custom.xml");
    logger.log("[OfficeMeta] Seccussfully set meta data in "+filePath);
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


    if (zip_name_locate(za, "docProps/custom.xml", 0) == -1)
    {
        zip_close(za);
        return -1;
    }
    
    std::string content;
    writeToStr(za, "docProps/custom.xml", content);

    const std::string fstr = "name=\""+name+"\">";
    const std::string fvp = "<vt:lpwstr>";
    const std::string lvp = "</vt:lpwstr>";
    std::size_t indx = content.rfind(fstr.c_str());
    if (indx != std::string::npos)
    {
        indx += fstr.size() + fvp.size();
        std::size_t n = content.find(lvp.c_str(),indx) - indx;
        value = content.substr(indx, n);
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

    if (zip_name_locate(za, "docProps/custom.xml", 0) == -1)
    {
        zip_close(za);
        return -1;
    }

    std::string content;
    writeToStr(za, "docProps/custom.xml", content);

    const std::string fstr = "name=\""+name+"\">";
    std::size_t indx = content.rfind(fstr.c_str());
    if (indx != std::string::npos)
    {
        indx = content.rfind("<property ", indx);
        std::size_t n = (content.find("</property>", indx) + 11) - indx;
        content.erase(indx, n);
    }
    
    zip_source_t *zs = zip_source_buffer(za, content.c_str(), content.size(), 0);
    if (!zs)
    {
        printf("Zsource error");
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
    zip_source_close(zs);

    zip_close(za);
    
    return 0;

}


void OfficeMeta::writeToStr(zip_t *za, const std::string &fileName, std::string &buffer)
{
    zip_file_t *zf = zip_fopen(za, fileName.c_str(),0);
    std::vector<char> buff(4096);
    zip_int64_t n;
    while ((n = zip_fread(zf, buff.data(), buff.size())) > 0) {
        buffer.append(buff.data(), n);
    }
    zip_fclose(zf);
}