#ifndef PROJECT_REPOSITORY_H
#define PROJECT_REPOSITORY_H

#include "tag_repository.h"
#include "task_repository.h"
#include "../dto/project_dto.h"
#include "../sql/sqlite3_handler.h"

class ProjectRepository {
    SQLite3Handler& sqlHandler;
    TaskRepository& taskRepository;
    TagRepository& tagRepository;
public:
    ProjectRepository(SQLite3Handler& sqlHandler, TaskRepository& taskRepository, TagRepository& tagRepository);
    ~ProjectRepository() = default;

    void insertProject(const std::string &projectId, const std::string &projectOwnerId, const std::string &projectName) const;
    void deleteProject(const std::string &projectId) const;
    [[nodiscard]] std::vector<ProjectMeta> listProjects(const std::string &userId) const;
    [[nodiscard]] std::unique_ptr<ProjectInfo> getProjectInfo(const std::string &projectId) const;
    void inviteMember(const std::string& projectId, const std::string& memberId) const;
    void kickMember(const std::string& projectId, const std::string& memberId) const;
    [[nodiscard]] std::string getProjectName(std::string projectId) const;
};

#endif //PROJECT_REPOSITORY_H