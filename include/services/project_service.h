#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H

#include <vector>

#include "notification_service.h"
#include "../repositories/project_repository.h"
#include "../dto/project_dto.h"
#include "../repositories/user_repository.h"

class ProjectService {
    ProjectRepository& projectRepository;
    UserRepository& userRepository;
    NotificationService& notificationService;
public:
    ProjectService(
        ProjectRepository& projectRepository, UserRepository& userRepository, NotificationService& notificationService
    );
    ~ProjectService() = default;

    [[nodiscard]] std::string createProject(const std::string &projectOwnerId, const std::string &projectName) const;
    void deleteProject(const std::string& userId, const std::string &projectId) const;
    [[nodiscard]] std::vector<ProjectMeta> listProjects(const std::string &userId) const;
    [[nodiscard]] std::unique_ptr<ProjectInfo> getProjectInfo(const std::string &projectId) const;
    void inviteMember(const std::string& userId, const std::string &projectId, const std::string &memberId) const;
    void kickMember(const std::string& userId, const std::string &projectId, const std::string &memberId) const;
};

#endif //PROJECT_SERVICE_H