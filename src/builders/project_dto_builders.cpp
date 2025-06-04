#include <stdexcept>

#include "../../include/builder/project_dto_builders.h"

ProjectMetaBuilder& ProjectMetaBuilder::setId(std::string id) {
    if (id.empty()) {
        throw std::invalid_argument("ID cannot be empty");
    }

    this->id = std::move(id);

    return *this;
}

ProjectMetaBuilder& ProjectMetaBuilder::setName(std::string name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }

    this->name = std::move(name);

    return *this;
}

std::unique_ptr<ProjectMeta> ProjectMetaBuilder::build() {
    if (id.empty() || name.empty()) {
        throw std::runtime_error("Required fields are not set");
    }

    return std::make_unique<ProjectMeta>(std::move(id), std::move(name));
}


ProjectInfoBuilder &ProjectInfoBuilder::setName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }

    this->name = name;

    return *this;
}

ProjectInfoBuilder &ProjectInfoBuilder::setOwnerId(std::string ownerId) {
    if (ownerId.empty()) {
        throw std::invalid_argument("OwnerId cannot be empty");
    }

    this->ownerId = std::move(ownerId);

    return *this;
}

ProjectInfoBuilder &ProjectInfoBuilder::addTag(const TagInfo &tag) {
    tags.push_back(tag);

    return *this;
}

ProjectInfoBuilder &ProjectInfoBuilder::addMember(const UserInfo &user) {
    members.push_back(user);

    return *this;
}

ProjectInfoBuilder &ProjectInfoBuilder::addTask(const TaskInfo &task) {
    tasks.push_back(task);

    return *this;
}

std::unique_ptr<ProjectInfo> ProjectInfoBuilder::build() {
    if (name.empty() || ownerId.empty()) {
        throw std::invalid_argument("Required fields are not set");
    }

    return std::make_unique<ProjectInfo>(name, ownerId, tags, members, tasks);
}