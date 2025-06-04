#include <utility>

#include "../../include/dto/task_dto.h"

TaskCreationData::TaskCreationData(
    std::string projectId, std::string taskName
) : projectId(std::move(projectId)), taskName(std::move(taskName)) {}

std::string TaskCreationData::getProjectId() const {
    return projectId;
}

std::string TaskCreationData::getTaskName() const {
    return taskName;
}

TaskCreationData TaskCreationData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto projectId = json.operator*()["project_id"].asString();
    const auto taskName = json.operator*()["task_name"].asString();

    return {projectId, taskName};
}


TaskNameUpdateData::TaskNameUpdateData(
    std::string taskId, std::string taskName
) : taskId(std::move(taskId)), taskName(std::move(taskName)) {}

std::string TaskNameUpdateData::getTaskId() const {
    return taskId;
}

std::string TaskNameUpdateData::getTaskName() const {
    return taskName;
}

TaskNameUpdateData TaskNameUpdateData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto projectId = json.operator*()["task_id"].asString();
    const auto taskName = json.operator*()["task_name"].asString();

    return {projectId, taskName};
}


TaskDescriptionUpdateData::TaskDescriptionUpdateData(
    std::string taskId, std::string taskDescription
) : taskId(std::move(taskId)), taskDescription(std::move(taskDescription)) {}

std::string TaskDescriptionUpdateData::getTaskId() const {
    return taskId;
}

std::string TaskDescriptionUpdateData::getTaskDescription() const {
    return taskDescription;
}

TaskDescriptionUpdateData TaskDescriptionUpdateData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto projectId = json.operator*()["task_id"].asString();
    const auto taskDescription = json.operator*()["task_description"].asString();

    return {projectId, taskDescription};
}


TaskPriorityUpdateData::TaskPriorityUpdateData(
    std::string taskId, const TaskPriority taskPriority
) : taskId(std::move(taskId)), taskPriority(taskPriority) {}

std::string TaskPriorityUpdateData::getTaskId() const {
    return taskId;
}

TaskPriority TaskPriorityUpdateData::getTaskPriority() const {
    return taskPriority;
}

TaskPriorityUpdateData TaskPriorityUpdateData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto projectId = json.operator*()["task_id"].asString();
    const auto taskPriorityName = json.operator*()["task_priority"].asString();
    TaskPriority taskPriority;

    if (taskPriorityName == "LOW") {
        taskPriority = LOW;
    } else if (taskPriorityName == "MEDIUM") {
        taskPriority = MEDIUM;
    } else {
        taskPriority = HIGH;
    }

    return {projectId, taskPriority};
}


TaskStatusUpdateData::TaskStatusUpdateData(
    std::string taskId, const TaskStatus taskStatus
) : taskId(std::move(taskId)), taskStatus(taskStatus) {}

std::string TaskStatusUpdateData::getTaskId() const {
    return taskId;
}

TaskStatus TaskStatusUpdateData::getTaskStatus() const {
    return taskStatus;
}

TaskStatusUpdateData TaskStatusUpdateData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto projectId = json.operator*()["task_id"].asString();
    const auto taskStatusName = json.operator*()["task_status"].asString();
    TaskStatus taskStatus;

    if (taskStatusName == "TODO") {
        taskStatus = TODO;
    } else if (taskStatusName == "IN_PROGRESS") {
        taskStatus = IN_PROGRESS;
    } else {
        taskStatus = COMPLETED;
    }

    return {projectId, taskStatus};
}


TaskAssigneeUpdateData::TaskAssigneeUpdateData(
    std::string taskId, std::string taskExecutorId
) : taskId(std::move(taskId)), taskAssigneeId(std::move(taskExecutorId)) {}

std::string TaskAssigneeUpdateData::getTaskId() const {
    return taskId;
}

std::string TaskAssigneeUpdateData::getTaskAssigneeId() const {
    return taskAssigneeId;
}

TaskAssigneeUpdateData TaskAssigneeUpdateData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto taskId = json.operator*()["task_id"].asString();
    const auto taskAssigneeId = json.operator*()["task_assignee_id"].asString();

    return {taskId, taskAssigneeId};
}


TaskTagsUpdateData::TaskTagsUpdateData(
    std::string taskId, std::string tagId
) : taskId(std::move(taskId)), tagId(std::move(tagId)) {}

std::string TaskTagsUpdateData::getTaskId() const {
    return taskId;
}

std::string TaskTagsUpdateData::getTagId() const {
    return tagId;
}

TaskTagsUpdateData TaskTagsUpdateData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto taskId = json.operator*()["task_id"].asString();
    const auto tagId = json.operator*()["tag_id"].asString();

    return {taskId, tagId};
}


TaskInfo::TaskInfo(
    std::string taskId, std::string taskName, std::string taskDescription,
    const TaskPriority taskPriority, const TaskStatus taskStatus, std::string assigneeId,
    std::vector<std::string> tags, std::vector<CommentInfo> comments
) : id(std::move(taskId)), name(std::move(taskName)),
    description(std::move(taskDescription)), priority(taskPriority), status(taskStatus),
    assigneeId(std::move(assigneeId)), tags(std::move(tags)), comments(std::move(comments)) {}

std::string TaskInfo::getId() const {
    return id;
}

std::string TaskInfo::getName() const {
    return name;
}

std::string TaskInfo::getDescription() const {
    return description;
}

TaskPriority TaskInfo::getPriority() const {
    return priority;
}

TaskStatus TaskInfo::getStatus() const {
    return status;
}

std::string TaskInfo::getAssigneeId() const {
    return assigneeId;
}

std::vector<std::string> TaskInfo::getTags() const {
    return tags;
}

std::vector<CommentInfo> TaskInfo::getComments() const {
    return comments;
}

std::unique_ptr<Json::Value> TaskInfo::toJson() const {
    Json::Value json;

    json["id"] = id;
    json["name"] = name;
    json["description"] = description;
    json["priority"] = priority;
    json["status"] = status;
    json["assignee_id"] = assigneeId;
    json["tags"] = Json::arrayValue;
    json["comments"] = Json::arrayValue;

    for (const auto& tag : tags) {
        json["tags"].append(tag);
    }

    for (const auto& comment : comments) {
        json["comments"].append(*comment.toJson());
    }

    return std::make_unique<Json::Value>(json);
}