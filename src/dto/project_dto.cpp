#include "../../include/dto/project_dto.h"

ProjectMeta::ProjectMeta(std::string id, std::string name) : id(std::move(id)), name(std::move(name)) {}

std::string ProjectMeta::getId() const {
    return id;
}

std::string ProjectMeta::getName() const {
    return name;
}

std::unique_ptr<Json::Value> ProjectMeta::toJson() const {
    Json::Value json;

    json["id"] = id;
    json["name"] = name;

    return std::make_unique<Json::Value>(json);
}

ProjectInfo::ProjectInfo(
    std::string name, std::string ownerId, std::vector<TagInfo> tags,
    std::vector<UserInfo> members, std::vector<TaskInfo> tasks
) : name(std::move(name)),
    ownerId(std::move(ownerId)),
    tags(std::move(tags)),
    members(std::move(members)),
    tasks(std::move(tasks)){}

std::string ProjectInfo::getName() const {
    return name;
}

std::string ProjectInfo::getOwnerId() const {
    return ownerId;
}

std::vector<TagInfo> ProjectInfo::getTags() const {
    return tags;
}

std::vector<UserInfo> ProjectInfo::getMembers() const {
    return members;
}

std::vector<TaskInfo> ProjectInfo::getTasks() const {
    return tasks;
}

std::unique_ptr<Json::Value> ProjectInfo::toJson() const {
    Json::Value json;

    json["name"] = name;
    json["owner_id"] = ownerId;
    json["tags"] = Json::Value(Json::arrayValue);
    json["members"] = Json::Value(Json::arrayValue);
    json["tasks"] = Json::arrayValue;

    for (auto& tag : tags) {
        json["tags"].append(*tag.toJson());
    }

    for (auto& member : members) {
        json["members"].append(*member.toJson());
    }

    for (auto& task : tasks) {
        json["tasks"].append(*task.toJson());
    }

    return std::make_unique<Json::Value>(json);
}


ProjectMemberData::ProjectMemberData(
    std::string projectId, std::string memberId
)  : projectId(std::move(projectId)), memberId(std::move(memberId)) {}

std::string ProjectMemberData::getProjectId() const {
    return projectId;
}

std::string ProjectMemberData::getMemberId() const {
    return memberId;
}

ProjectMemberData ProjectMemberData::fromJson(const std::shared_ptr<Json::Value>& json) {
    std::string projectId = json.operator*()["project_id"].asString();
    std::string memberId = json.operator*()["member_id"].asString();

    return {projectId, memberId};
}