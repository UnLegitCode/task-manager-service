#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

#include "comment_repository.h"
#include "../dto/task_dto.h"
#include "../services/notification_service.h"
#include "../sql/sqlite3_handler.h"

class TaskRepository {
    SQLite3Handler& sqlHandler;
    CommentRepository& commentRepository;
public:
    TaskRepository(SQLite3Handler& sqlHandler, CommentRepository& commentRepository);
    ~TaskRepository() = default;

    void insertTask(std::string projectId, std::string taskId, std::string taskName) const;
    void deleteTask(std::string taskId) const;
    void updateTaskName(std::string taskId, std::string taskName) const;
    void updateTaskDescription(std::string taskId, std::string taskDescription) const;
    void updateTaskPriority(std::string taskId, TaskPriority taskPriority) const;
    void updateTaskStatus(std::string taskId, TaskStatus taskStatus) const;
    void updateTaskAssignee(std::string taskId, std::string taskAssigneeId) const;
    void addTagToTask(std::string taskId, std::string tagId) const;
    void deleteTagFromTask(std::string taskId, std::string tagId) const;
    [[nodiscard]] std::unique_ptr<TaskInfo> getTaskInfo(std::string taskId) const;
    [[nodiscard]] std::vector<TaskInfo> getProjectTasks(std::string projectId) const;
    [[nodiscard]] std::string getTaskName(std::string taskId) const;
    [[nodiscard]] std::string getTaskProjectId(std::string taskId) const;
};

#endif //TASK_REPOSITORY_H