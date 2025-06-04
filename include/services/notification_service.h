#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include "../utilities/http_client.h"

class NotificationService {
    HttpClient client;
public:
    explicit NotificationService(const std::string &host);
    ~NotificationService() = default;

    void notifyProjectCreation(const std::string &userId, const std::string &projectName) const;
    void notifyProjectDeletion(const std::string &userId, const std::string &projectName) const;
    void notifyProjectMemberInvitation(const std::string &userId, const std::string &projectName, const std::string &memberName) const;
    void notifyProjectMemberKick(const std::string &userId, const std::string &projectName, const std::string &memberName) const;

    void notifyTaskCreation(const std::string &userId, const std::string &projectName, const std::string &taskName) const;
    void notifyTaskDeletion(const std::string &userId, const std::string &projectName, const std::string &taskName) const;
    void notifyTaskNameUpdate(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &newTaskName
    ) const;
    void notifyTaskDescriptionUpdate(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &newTaskDescription
    ) const;
    void notifyTaskPriorityUpdate(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &newTaskPriority
    ) const;
    void notifyTaskStatusUpdate(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &newTaskStatus
    ) const;
    void notifyTaskAssigneeUpdate(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &newTaskAssigneeName
    ) const;
    void notifyTaskTagAddition(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &tagName
    ) const;
    void notifyTaskTagDeletion(
        const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &tagName
    ) const;

    void notifyTagCreation(const std::string &userId, const std::string &projectName, const std::string &tagName) const;
    void notifyTagDeletion(const std::string &userId, const std::string &projectName, const std::string &tagName) const;

    void notifyCommentCreation(const std::string &userId, const std::string &taskName, const std::string &commentContent) const;
    void notifyCommentDeletion(const std::string &userId, const std::string &taskName, const std::string &commentContent) const;
};

#endif //NOTIFICATION_SERVICE_H