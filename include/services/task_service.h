#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "../dto/task_dto.h"
#include "../repositories/project_repository.h"
#include "../repositories/task_repository.h"
#include "../repositories/user_repository.h"

class TaskService {
    TaskRepository& taskRepository;
    ProjectRepository& projectRepository;
    UserRepository& userRepository;
    TagRepository& tagRepository;
    NotificationService& notificationService;
public:
    TaskService(
        TaskRepository& taskRepository, ProjectRepository& projectRepository, TagRepository& tagRepository,
        UserRepository& userRepository, NotificationService& notificationService
    );
    ~TaskService() = default;

    [[nodiscard]] std::string createTask(const std::string& userId, std::string projectId, std::string taskName) const;
    void deleteTask(const std::string& userId, std::string taskId) const;
    void updateTaskName(const std::string& userId, std::string taskId, std::string taskName) const;
    void updateTaskDescription(const std::string& userId, std::string taskId, std::string taskDescription) const;
    void updateTaskPriority(const std::string& userId, std::string taskId, TaskPriority taskPriority) const;
    void updateTaskStatus(const std::string& userId, std::string taskId, TaskStatus taskStatus) const;
    void updateTaskAssignee(const std::string& userId, std::string taskId, std::string taskAssigneeId) const;
    void addTagToTask(const std::string& userId, std::string taskId, std::string tagId) const;
    void deleteTagFromTask(const std::string& userId, std::string taskId, std::string tagId) const;
};

#endif //TASK_SERVICE_H