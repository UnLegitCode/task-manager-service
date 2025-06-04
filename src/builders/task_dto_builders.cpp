#include "../../include/builder/task_dto_builders.h"

TaskInfoBuilder &TaskInfoBuilder::setId(std::string id) {
    if (id.empty()) {
        throw std::invalid_argument("ID cannot be empty");
    }

    this->id = std::move(id);

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::setName(std::string name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }

    this->name = std::move(name);

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::setDescription(std::string description) {
    if (description.empty()) {
        throw std::invalid_argument("Description cannot be empty");
    }

    this->description = std::move(description);

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::setPriority(TaskPriority priority) {
    this->priority = priority;

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::setStatus(TaskStatus status) {
    this->status = status;

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::setAssigneeId(std::string assigneeId) {
    if (assigneeId.empty()) {
        throw std::invalid_argument("Assignee id cannot be empty");
    }

    this->assigneeId = std::move(assigneeId);

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::addTag(std::string tag) {
    tags.push_back(std::move(tag));

    return *this;
}

TaskInfoBuilder &TaskInfoBuilder::addComment(CommentInfo comment) {
    comments.push_back(std::move(comment));

    return *this;
}

std::unique_ptr<TaskInfo> TaskInfoBuilder::build() {
    if (id.empty() || name.empty() || description.empty() || assigneeId.empty()) {
        throw std::invalid_argument("Required fields are not set");
    }

    return std::make_unique<TaskInfo>(id, name, description, priority, status, assigneeId, tags, comments);
}