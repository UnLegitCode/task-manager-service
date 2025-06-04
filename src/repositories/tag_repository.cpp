#include "../../include/repositories/tag_repository.h"

TagRepository::TagRepository(SQLite3Handler& sqlHandler) : sqlHandler(sqlHandler) {
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `tags`(`id` VARCHAR(36) PRIMARY KEY, `name` VARCHAR(32));");
}

void TagRepository::insertTag(
    const std::string& projectId, const std::string& tagId, const std::string& tagName
) const {
    sqlHandler.update("INSERT INTO `tags`(`id`, `name`) VALUES(:id, :name);", {
        {":id", tagId},
        {":name", tagName}
    });
    sqlHandler.update("INSERT INTO `project_tags`(`project_id`, `tag_id`) VALUES(:project_id, :tag_id);", {
        {":project_id", projectId},
        {":tag_id", tagId}
    });
}

void TagRepository::deleteTag(const std::string& tagId) const {
    sqlHandler.update("DELETE FROM `tags` WHERE `id`=:tag_id;", {
        {":tag_id", tagId}
    });
    sqlHandler.update("DELETE FROM `project_tags` WHERE `tag_id`=:tag_id;", {
        {":tag_id", tagId}
    });
}

std::vector<TagInfo> TagRepository::getProjectTasks(const std::string &projectId) const {
    std::vector<std::map<std::string, std::string>> projectTags = sqlHandler.fetch("SELECT pt.tag_id, t.name FROM project_tags pt JOIN tags t ON pt.tag_id = t.id WHERE pt.project_id = :project_id;", {
        {":project_id", projectId}
    });
    std::vector<TagInfo> tags;

    tags.reserve(projectTags.size());

    for (auto& tagData : projectTags) {
        tags.emplace_back(tagData.at("tag_id"), tagData.at("name"));
    }

    return tags;
}

std::string TagRepository::getTagName(const std::string &tagId) const {
    return sqlHandler.fetch("SELECT `name` FROM `tags` WHERE `id`=:tag_id LIMIT 1;", {
        {":tag_id", tagId}
    })[0].at("name");
}

std::string TagRepository::getTagProjectId(std::string tagId) const {
    return sqlHandler.fetch("SELECT `project_id` FROM `project_tags` WHERE `tag_id`=:tag_id LIMIT 1;", {
        {":tag_id", tagId}
    })[0].at("project_id");
}
