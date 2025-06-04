#ifndef TASK_DTO_BUILDERS_H
#define TASK_DTO_BUILDERS_H

#include <string>

#include "builder.h"
#include "../dto/task_dto.h"

class TaskInfoBuilder final : public Builder<TaskInfo> {
    std::string id{};
    std::string name{};
    std::string description{};
    TaskPriority priority{};
    TaskStatus status{};
    std::string assigneeId{};
    std::vector<std::string> tags{};
    std::vector<CommentInfo> comments{};
public:
    TaskInfoBuilder() = default;
    ~TaskInfoBuilder() override = default;

    TaskInfoBuilder& setId(std::string id);
    TaskInfoBuilder& setName(std::string name);
    TaskInfoBuilder& setDescription(std::string description);
    TaskInfoBuilder& setPriority(TaskPriority priority);
    TaskInfoBuilder& setStatus(TaskStatus status);
    TaskInfoBuilder& setAssigneeId(std::string assigneeId);
    TaskInfoBuilder& addTag(std::string tag);
    TaskInfoBuilder& addComment(CommentInfo comment);
    std::unique_ptr<TaskInfo> build() override;
};

#endif //TASK_DTO_BUILDERS_H