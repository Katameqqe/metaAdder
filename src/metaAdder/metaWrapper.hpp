#include "metaProcessor.hpp"
#include <memory>

class metaWrapper {
public:
    metaWrapper(std::string filePath)
    {
        filePath_ = filePath;
        std::string ext = filePath_.substr(filePath_.find_last_of(".") + 1);
        if (ext == "pdf")
        {
            adder_ = std::unique_ptr<metaAdder>(new PDFMetaAdder());
        }
        else
        {
            adder_ = std::unique_ptr<metaAdder>(new XAttrMetaAdder());
        }
    }

    int setMeta(const std::string &name, const std::string &value) {
        return adder_->setMeta(filePath_, name, value);
    }

    int getMeta(const std::string &name, std::string &value) {
        return adder_->getMeta(filePath_, name, value);
    }

    int removeMeta(const std::string &name) {
        return adder_->removeMeta(filePath_, name);
    }

    int listMeta(std::vector<std::string> &list) {
        return adder_->listMeta(filePath_, list);
    }
private:
    std::unique_ptr<metaAdder> adder_;
    std::string filePath_;
};