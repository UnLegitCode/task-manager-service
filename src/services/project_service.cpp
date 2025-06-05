    #include "../../include/services/project_service.h"
    #include "../../include/utilities/utility.h"

    ProjectService::ProjectService(
        ProjectRepository &projectRepository, UserRepository& userRepository, NotificationService &notificationService
    ) : projectRepository(projectRepository), userRepository(userRepository), notificationService(notificationService) {}

    std::string ProjectService::createProject(const std::string& projectOwnerId, const std::string& projectName) const {
        std::string projectId = generateUUID();

        projectRepository.insertProject(projectId, projectOwnerId, projectName);

        notificationService.notifyProjectCreation(projectOwnerId, projectName);

        return projectId;
    }

    void ProjectService::deleteProject(const std::string& userId, const std::string& projectId) const {
        notificationService.notifyProjectDeletion(userId, projectRepository.getProjectName(projectId));

        projectRepository.deleteProject(projectId);
    }

    std::vector<ProjectMeta> ProjectService::listProjects(const std::string& userId) const {
        return projectRepository.listProjects(userId);
    }

    std::unique_ptr<ProjectInfo> ProjectService::getProjectInfo(const std::string& projectId) const {
        return projectRepository.getProjectInfo(projectId);
    }

    void ProjectService::inviteMember(
        const std::string& userId,, const std::string& projectId, const std::string& memberId
    ) const {
        projectRepository.inviteMember(projectId, memberId);

        notificationService.notifyProjectMemberInvitation(
            userId, projectRepository.getProjectName(projectId), userRepository.getUsername(userId)
        );
    }

    void ProjectService::kickMember(
        const std::string& userId, const std::string& projectId, const std::string& memberId
    ) const {
        projectRepository.kickMember(projectId, memberId);

        notificationService.notifyProjectMemberKick(
            userId, projectRepository.getProjectName(projectId), userRepository.getUsername(userId)
        );
    }