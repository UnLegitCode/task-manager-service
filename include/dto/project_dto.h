#ifndef PROJECT_DTO_H
#define PROJECT_DTO_H

#include <string>
#include <vector>

#include "tag_dto.h"
#include "task_dto.h"
#include "user_dto.h"

class ProjectMeta {
    std::string id;
    std::string name;

public:
    ProjectMeta(std::string id, std::string name);
    ~ProjectMeta() = default;

    [[nodiscard]] std::string getId() const;
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::unique_ptr<Json::Value> toJson() const;
};

class ProjectInfo {
    std::string name;
    std::string ownerId;
    std::vector<TagInfo> tags;
    std::vector<UserInfo> members;
    std::vector<TaskInfo> tasks;

public:
    ProjectInfo(
        std::string name, std::string ownerId, std::vector<TagInfo> tags,
        std::vector<UserInfo> members, std::vector<TaskInfo> tasks
    );
    ~ProjectInfo() = default;

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getOwnerId() const;
    [[nodiscard]] std::vector<TagInfo> getTags() const;
    [[nodiscard]] std::vector<UserInfo> getMembers() const;
    [[nodiscard]] std::vector<TaskInfo> getTasks() const;

    [[nodiscard]] std::unique_ptr<Json::Value> toJson() const;
};

class ProjectMemberData {
    std::string projectId;
    std::string memberId;
public:
    ProjectMemberData(std::string projectId, std::string memberId);
    ~ProjectMemberData() = default;

    [[nodiscard]] std::string getProjectId() const;
    [[nodiscard]] std::string getMemberId() const;

    static ProjectMemberData fromJson(const std::shared_ptr<Json::Value>& json);
};

#endif //PROJECT_DTO_H