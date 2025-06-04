#include "../../include/repositories/project_repository.h"

#include "../../include/builder/project_dto_builders.h"

ProjectRepository::ProjectRepository(
    SQLite3Handler &sqlHandler, TaskRepository &taskRepository, TagRepository &tagRepository
) : sqlHandler(sqlHandler), taskRepository(taskRepository), tagRepository(tagRepository) {
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `projects`(`id` VARCHAR(36) PRIMARY KEY, `name` VARCHAR(32), `owner_id` VARCHAR(36));");
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `project_members`(`project_id` VARCHAR(36), `member_id` VARCHAR(36));");
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `project_tags`(`project_id` VARCHAR(36), `tag_id` VARCHAR(36));");
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `project_tasks`(`project_id` VARCHAR(36), `task_id` VARCHAR(36));");
}

void ProjectRepository::insertProject(
    const std::string& projectId, const std::string& projectOwnerId, const std::string& projectName
) const {
    sqlHandler.update("INSERT INTO `projects`(`id`,`name`,`owner_id`) VALUES(:id, :name, :owner_id);", {
        {":id", projectId},
        {":name", projectName},
        {":owner_id", projectOwnerId}
    });
}

void ProjectRepository::deleteProject(const std::string& projectId) const {
    sqlHandler.update("DELETE FROM `projects` WHERE `id`=:project_id;", {
        {":project_id", projectId}
    });
}

std::vector<ProjectMeta> ProjectRepository::listProjects(const std::string& userId) const {
    std::vector<std::map<std::string, std::string>> ownProjects = sqlHandler.fetch("SELECT `id`, `name` FROM `projects` WHERE `owner_id`=:owner_id;", {
        {":owner_id", userId}
    });
    std::vector<std::map<std::string, std::string>> memberProjects = sqlHandler.fetch("SELECT pm.project_id, p.name FROM project_members pm INNER JOIN projects p ON pm.project_id = p.id WHERE pm.member_id = :member_id;", {
        {":member_id", userId}
    });
    std::vector<ProjectMeta> projectList;

    projectList.reserve(ownProjects.size() + memberProjects.size());

    for (auto& projectData : ownProjects) {
        projectList.push_back(ProjectMetaBuilder()
            .setId(projectData.at("id"))
            .setName(projectData.at("name"))
            .build()
            .operator*()
        );
    }

    for (auto& projectData : memberProjects) {
        projectList.emplace_back(projectData.at("project_members.project_id"), projectData.at("p.name"));
    }

    return projectList;
}

std::unique_ptr<ProjectInfo> ProjectRepository::getProjectInfo(const std::string& projectId) const {
    const std::map<std::string, std::string> projectData = sqlHandler.fetch("SELECT `name`, `owner_id` FROM `projects` WHERE `id`=:project_id LIMIT 1;", {
        {":project_id", projectId}
    })[0];

    ProjectInfoBuilder& builder = ProjectInfoBuilder()
        .setName(projectData.at("name"))
        .setOwnerId(projectData.at("owner_id"));

    std::vector<std::map<std::string, std::string>> projectMembers = sqlHandler.fetch("SELECT pm.member_id, u.username FROM project_members pm INNER JOIN users u ON pm.member_id = u.id WHERE pm.project_id = :project_id;", {
        {":project_id", projectId}
    });

    for (auto& memberData : projectMembers) {
        builder.addMember(UserInfo(memberData.at("pm.member_id"), memberData.at("u.name")));
    }

    for (const std::vector<TagInfo> tags = tagRepository.getProjectTasks(projectId); const auto & tag : tags) {
        builder.addTag(tag);
    }

    for (const std::vector<TaskInfo> tasks = taskRepository.getProjectTasks(projectId); const auto& task : tasks) {
        builder.addTask(task);
    }

    return builder.build();
}

void ProjectRepository::inviteMember(const std::string &projectId, const std::string &memberId) const {
    sqlHandler.update("INSERT INTO project_members(project_id, member_id) VALUES(:project_id, :member_id);", {
        {":project_id", projectId},
        {":member_id", memberId}
    });
}

void ProjectRepository::kickMember(const std::string& projectId, const std::string& memberId) const {
    sqlHandler.update("DELETE FROM project_members WHERE project_id=:project_id AND member_id=:member_id;", {
        {":project_id", projectId},
        {":member_id", memberId}
    });
}

std::string ProjectRepository::getProjectName(std::string projectId) const {
    return sqlHandler.fetch("SELECT `name` FROM `projects` WHERE `project_id`=:project_id LIMIT 1;", {
        {":project_id", projectId}
    })[0].at("name");
}