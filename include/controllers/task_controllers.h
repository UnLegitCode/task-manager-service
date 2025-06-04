#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

#include <drogon/HttpSimpleController.h>

class TaskCreationController final : public drogon::HttpSimpleController<TaskCreationController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/create", drogon::Post);
    PATH_LIST_END
};

class TaskDeletionController final : public drogon::HttpSimpleController<TaskDeletionController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/delete", drogon::Delete);
    PATH_LIST_END
};

class TaskNameUpdateController final : public drogon::HttpSimpleController<TaskNameUpdateController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/update/name", drogon::Patch);
    PATH_LIST_END
};

class TaskDescriptionUpdateController final : public drogon::HttpSimpleController<TaskDescriptionUpdateController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/update/description", drogon::Patch);
    PATH_LIST_END
};

class TaskPriorityUpdateController final : public drogon::HttpSimpleController<TaskPriorityUpdateController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/update/priority", drogon::Patch);
    PATH_LIST_END
};

class TaskStatusUpdateController final : public drogon::HttpSimpleController<TaskStatusUpdateController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/update/status", drogon::Patch);
    PATH_LIST_END
};

class TaskAssigneeUpdateController final : public drogon::HttpSimpleController<TaskAssigneeUpdateController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/update/assignee", drogon::Patch);
    PATH_LIST_END
};

class TaskTagAdditionController final : public drogon::HttpSimpleController<TaskTagAdditionController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/tags/add", drogon::Post);
    PATH_LIST_END
};

class TaskTagDeletionController final : public drogon::HttpSimpleController<TaskTagDeletionController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tasks/tags/delete", drogon::Delete);
    PATH_LIST_END
};

#endif //TASK_CONTROLLER_H