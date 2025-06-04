#include "../../include/dto/tag_dto.h"

TagInfo::TagInfo(std::string id, std::string name) : id(std::move(id)), name(std::move(name)) {}

std::string TagInfo::getId() const {
    return id;
}

std::string TagInfo::getName() const {
    return name;
}

std::unique_ptr<Json::Value> TagInfo::toJson() const {
    Json::Value json;

    json["id"] = id;
    json["name"] = name;

    return std::make_unique<Json::Value>(json);
}


TagCreationData::TagCreationData(
    std::string projectId, std::string tagName
) : projectId(std::move(projectId)), tagName(std::move(tagName)) {}

std::string TagCreationData::getProjectId() const {
    return projectId;
}

std::string TagCreationData::getTagName() const {
    return tagName;
}

TagCreationData TagCreationData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto projectId = json.operator*()["project_id"].asString();
    const auto tagName = json.operator*()["tag_name"].asString();

    return {projectId, tagName};
}