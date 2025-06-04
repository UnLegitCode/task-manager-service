#include "../../include/services/notification_service.h"

NotificationService::NotificationService(const std::string& host) : client(HttpClient(host)) {}

void NotificationService::notifyProjectCreation(const std::string &userId, const std::string &projectName) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;

    client.sendAsyncRequest(drogon::Post, "/projects/create", requestBody);
}

void NotificationService::notifyProjectDeletion(const std::string &userId, const std::string &projectName) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;

    client.sendAsyncRequest(drogon::Delete, "/projects/delete", requestBody);
}

void NotificationService::notifyProjectMemberInvitation(
    const std::string &userId, const std::string &projectName, const std::string &memberName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["member_name"] = memberName;

    client.sendAsyncRequest(drogon::Post, "/projects/invite", requestBody);
}

void NotificationService::notifyProjectMemberKick(
    const std::string &userId, const std::string &projectName, const std::string &memberName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["member_name"] = memberName;

    client.sendAsyncRequest(drogon::Post, "/projects/kick", requestBody);
}


void NotificationService::notifyTaskCreation(
    const std::string &userId, const std::string &projectName, const std::string &taskName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;

    client.sendAsyncRequest(drogon::Post, "/tasks/create", requestBody);
}

void NotificationService::notifyTaskDeletion(
    const std::string &userId, const std::string &projectName, const std::string &taskName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;

    client.sendAsyncRequest(drogon::Delete, "/tasks/delete", requestBody);
}

void NotificationService::notifyTaskNameUpdate(
    const std::string &userId, const std::string &projectName,
    const std::string &taskName, const std::string &newTaskName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["new_task_name"] = newTaskName;

    client.sendAsyncRequest(drogon::Post, "/tasks/update/name", requestBody);
}

void NotificationService::notifyTaskDescriptionUpdate(
    const std::string &userId, const std::string &projectName,
    const std::string &taskName, const std::string &newTaskDescription
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["new_task_description"] = newTaskDescription;

    client.sendAsyncRequest(drogon::Post, "/tasks/update/description", requestBody);
}

void NotificationService::notifyTaskPriorityUpdate(
    const std::string &userId, const std::string &projectName,
    const std::string &taskName, const std::string &newTaskPriority
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["new_task_priority"] = newTaskPriority;

    client.sendAsyncRequest(drogon::Post, "/tasks/update/priority", requestBody);
}

void NotificationService::notifyTaskStatusUpdate(
    const std::string &userId, const std::string &projectName,
    const std::string &taskName, const std::string &newTaskStatus
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["new_task_status"] = newTaskStatus;

    client.sendAsyncRequest(drogon::Post, "/tasks/update/status", requestBody);
}

void NotificationService::notifyTaskAssigneeUpdate(
    const std::string &userId, const std::string &projectName,
    const std::string &taskName, const std::string &newTaskAssigneeName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["new_task_assignee_name"] = newTaskAssigneeName;

    client.sendAsyncRequest(drogon::Post, "/tasks/update/assignee", requestBody);
}

void NotificationService::notifyTaskTagAddition(
    const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &tagName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["tag_name"] = tagName;

    client.sendAsyncRequest(drogon::Post, "/tasks/tags/add", requestBody);
}

void NotificationService::notifyTaskTagDeletion(
    const std::string &userId, const std::string &projectName, const std::string &taskName, const std::string &tagName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["task_name"] = taskName;
    requestBody["tag_name"] = tagName;

    client.sendAsyncRequest(drogon::Post, "/tasks/tags/delete", requestBody);
}


void NotificationService::notifyTagCreation(
    const std::string &userId, const std::string &projectName, const std::string &tagName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["tag_name"] = tagName;

    client.sendAsyncRequest(drogon::Post, "/tags/create", requestBody);
}

void NotificationService::notifyTagDeletion(
    const std::string &userId, const std::string &projectName, const std::string &tagName
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["project_name"] = projectName;
    requestBody["tag_name"] = tagName;

    client.sendAsyncRequest(drogon::Delete, "/tags/delete", requestBody);
}


void NotificationService::notifyCommentCreation(
    const std::string &userId, const std::string &taskName, const std::string &commentContent
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["task_name"] = taskName;
    requestBody["comment_content"] = commentContent;

    client.sendAsyncRequest(drogon::Post, "/comments/create", requestBody);

}

void NotificationService::notifyCommentDeletion(
    const std::string &userId, const std::string &taskName, const std::string &commentContent
) const {
    Json::Value requestBody;

    requestBody["user_id"] = userId;
    requestBody["task_name"] = taskName;
    requestBody["comment_content"] = commentContent;

    client.sendAsyncRequest(drogon::Delete, "/comments/delete", requestBody);
}
