#ifndef PROJECT_DTO_BUILDERS_H
#define PROJECT_DTO_BUILDERS_H

#include <string>

#include "builder.h"
#include "../dto/project_dto.h"

class ProjectMetaBuilder final : public Builder<ProjectMeta> {
    std::string id;
    std::string name;
public:
    ProjectMetaBuilder() = default;
    ~ProjectMetaBuilder() override = default;

    ProjectMetaBuilder& setId(std::string id);
    ProjectMetaBuilder& setName(std::string name);
    std::unique_ptr<ProjectMeta> build() override;
};

class ProjectInfoBuilder final : public Builder<ProjectInfo> {
    std::string name;
    std::string ownerId;
    std::vector<TagInfo> tags{};
    std::vector<UserInfo> members{};
    std::vector<TaskInfo> tasks{};
public:
    ProjectInfoBuilder() = default;
    ~ProjectInfoBuilder() override = default;

    ProjectInfoBuilder& setName(const std::string &name);
    ProjectInfoBuilder& setOwnerId(std::string ownerId);
    ProjectInfoBuilder& addTag(const TagInfo& tag);
    ProjectInfoBuilder& addMember(const UserInfo& member);
    ProjectInfoBuilder& addTask(const TaskInfo& task);
    std::unique_ptr<ProjectInfo> build() override;
};

#endif //PROJECT_DTO_BUILDERS_H