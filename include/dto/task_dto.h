#ifndef TASK_DTO_H
#define TASK_DTO_H

#include <string>
#include <vector>
#include <json/value.h>

#include "comment_dto.h"

enum TaskPriority {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2,
};

enum TaskStatus {
    TODO = 0,
    IN_PROGRESS = 1,
    COMPLETED = 2,
};

class TaskCreationData {
    std::string projectId;
    std::string taskName;

public:
    TaskCreationData(std::string projectId, std::string taskName);
    ~TaskCreationData() = default;

    [[nodiscard]] std::string getProjectId() const;
    [[nodiscard]] std::string getTaskName() const;

    static TaskCreationData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskNameUpdateData {
    std::string taskId;
    std::string taskName;

public:
    TaskNameUpdateData(std::string taskId, std::string taskName);
    ~TaskNameUpdateData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] std::string getTaskName() const;

    static TaskNameUpdateData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskDescriptionUpdateData {
    std::string taskId;
    std::string taskDescription;

public:
    TaskDescriptionUpdateData(std::string taskId, std::string taskDescription);
    ~TaskDescriptionUpdateData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] std::string getTaskDescription() const;

    static TaskDescriptionUpdateData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskPriorityUpdateData {
    std::string taskId;
    TaskPriority taskPriority;

public:
    TaskPriorityUpdateData(std::string taskId, TaskPriority taskPriority);
    ~TaskPriorityUpdateData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] TaskPriority getTaskPriority() const;

    static TaskPriorityUpdateData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskStatusUpdateData {
    std::string taskId;
    TaskStatus taskStatus;

public:
    TaskStatusUpdateData(std::string taskId, TaskStatus taskStatus);
    ~TaskStatusUpdateData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] TaskStatus getTaskStatus() const;

    static TaskStatusUpdateData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskAssigneeUpdateData {
    std::string taskId;
    std::string taskAssigneeId;

public:
    TaskAssigneeUpdateData(std::string taskId, std::string taskExecutorId);
    ~TaskAssigneeUpdateData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] std::string getTaskAssigneeId() const;

    static TaskAssigneeUpdateData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskTagsUpdateData {
    std::string taskId;
    std::string tagId;

public:
    TaskTagsUpdateData(std::string taskId, std::string tagId);
    ~TaskTagsUpdateData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] std::string getTagId() const;

    static TaskTagsUpdateData fromJson(const std::shared_ptr<Json::Value>& json);
};

class TaskInfo {
    std::string id;
    std::string name;
    std::string description;
    TaskPriority priority;
    TaskStatus status;
    std::string assigneeId;
    std::vector<std::string> tags;
    std::vector<CommentInfo> comments;
public:
    TaskInfo(
        std::string taskId, std::string taskName, std::string taskDescription, TaskPriority taskPriority,
        TaskStatus taskStatus, std::string assigneeId, std::vector<std::string> tags, std::vector<CommentInfo> comments
    );
    ~TaskInfo() = default;

    [[nodiscard]] std::string getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] TaskPriority getPriority() const;
    [[nodiscard]] TaskStatus getStatus() const;
    [[nodiscard]] std::string getAssigneeId() const;
    [[nodiscard]] std::vector<std::string> getTags() const;
    [[nodiscard]] std::vector<CommentInfo> getComments() const;

    [[nodiscard]] std::unique_ptr<Json::Value> toJson() const;
};

#endif //TASK_DTO_H