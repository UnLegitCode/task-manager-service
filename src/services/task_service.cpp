#include "../../include/services/task_service.h"
#include "../../include/utilities/utility.h"

TaskService::TaskService(
    TaskRepository& taskRepository, ProjectRepository& projectRepository, TagRepository& tagRepository,
    UserRepository& userRepository, NotificationService& notificationService
) : taskRepository(taskRepository), projectRepository(projectRepository), tagRepository(tagRepository),
    userRepository(userRepository), notificationService(notificationService) {}

std::string TaskService::createTask(const std::string& userId, std::string projectId, std::string taskName) const {
    std::string taskId = generateUUID();

    taskRepository.insertTask(std::move(projectId), taskId, std::move(taskName));

    notificationService.notifyTaskCreation(userId, projectRepository.getProjectName(projectId), taskName);

    return taskId;
}

void TaskService::deleteTask(const std::string& userId, std::string taskId) const {
    taskRepository.deleteTask(std::move(taskId));

    notificationService.notifyTaskDeletion(
        userId,
        projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId)
    );
}

void TaskService::updateTaskName(const std::string& userId, std::string taskId, std::string taskName) const {
    taskRepository.updateTaskName(std::move(taskId), std::move(taskName));

    notificationService.notifyTaskNameUpdate(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), taskName
    );
}

void TaskService::updateTaskDescription(const std::string& userId, std::string taskId, std::string taskDescription) const {
    taskRepository.updateTaskDescription(std::move(taskId), std::move(taskDescription));

    notificationService.notifyTaskDescriptionUpdate(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), taskDescription
    );
}

void TaskService::updateTaskPriority(const std::string& userId, std::string taskId, const TaskPriority taskPriority) const {
    taskRepository.updateTaskPriority(std::move(taskId), taskPriority);

    std::string rawTaskPriority;

    if (taskPriority == LOW) {
        rawTaskPriority = "LOW";
    } else if (taskPriority == MEDIUM) {
        rawTaskPriority = "MEDIUM";
    } else {
        rawTaskPriority = "HIGH";
    }

    notificationService.notifyTaskPriorityUpdate(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), rawTaskPriority
    );
}

void TaskService::updateTaskStatus(const std::string& userId, std::string taskId, const TaskStatus taskStatus) const {
    taskRepository.updateTaskStatus(std::move(taskId), taskStatus);

    std::string rawTaskStatus;

    if (taskStatus == TODO) {
        rawTaskStatus = "TODO";
    } else if (taskStatus == IN_PROGRESS) {
        rawTaskStatus = "IN_PROGRESS";
    } else {
        rawTaskStatus = "COMPLETED";
    }

    notificationService.notifyTaskStatusUpdate(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), rawTaskStatus
    );
}

void TaskService::updateTaskAssignee(const std::string& userId, std::string taskId, std::string taskAssigneeId) const {
    taskRepository.updateTaskAssignee(std::move(taskId), std::move(taskAssigneeId));

    notificationService.notifyTaskAssigneeUpdate(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), userRepository.getUsername(taskAssigneeId)
    );
}

void TaskService::addTagToTask(const std::string& userId, std::string taskId, std::string tagId) const {
    taskRepository.addTagToTask(std::move(taskId), std::move(tagId));

    notificationService.notifyTaskTagAddition(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), tagRepository.getTagName(taskId)
    );
}

void TaskService::deleteTagFromTask(const std::string& userId, std::string taskId, std::string tagId) const {
    taskRepository.deleteTagFromTask(std::move(taskId), std::move(tagId));

    notificationService.notifyTaskTagDeletion(
        userId, projectRepository.getProjectName(taskRepository.getTaskProjectId(taskId)),
        taskRepository.getTaskName(taskId), tagRepository.getTagName(taskId)
    );
}