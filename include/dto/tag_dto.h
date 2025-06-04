#ifndef TAG_DTO_H
#define TAG_DTO_H

#include <string>
#include <json/value.h>

class TagInfo {
    std::string id;
    std::string name;

public:
    TagInfo(std::string id, std::string name);
    ~TagInfo() = default;

    [[nodiscard]] std::string getId() const;
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::unique_ptr<Json::Value> toJson() const;
};

class TagCreationData {
    std::string projectId;
    std::string tagName;

public:
    TagCreationData(std::string projectId, std::string tagName);
    ~TagCreationData() = default;

    [[nodiscard]] std::string getProjectId() const;
    [[nodiscard]] std::string getTagName() const;

    static TagCreationData fromJson(const std::shared_ptr<Json::Value>& json);
};

#endif //TAG_DTO_H