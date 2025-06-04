#include "../../include/controllers/task_controllers.h"

#include "../../include/instance_holder.h"
#include "../../include/dto/task_dto.h"

void TaskCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskCreationData taskCreationData = TaskCreationData::fromJson(req->jsonObject());
    const std::string taskId = InstanceHolder::getInstance()->getTaskService()->createTask(
        taskCreationData.getProjectId(), taskCreationData.getTaskName()
    );
    Json::Value responseBody;

    responseBody["task_id"] = taskId;

    callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
}

void TaskDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const auto taskId = req->getJsonObject().operator*()["task_id"].asString();

    InstanceHolder::getInstance()->getTaskService()->deleteTask(taskId);

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskNameUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskNameUpdateData updateData = TaskNameUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->updateTaskName(updateData.getTaskId(), updateData.getTaskName());

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskDescriptionUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskDescriptionUpdateData updateData = TaskDescriptionUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->updateTaskDescription(
        updateData.getTaskId(), updateData.getTaskDescription()
    );

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskPriorityUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskPriorityUpdateData updateData = TaskPriorityUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->updateTaskPriority(
        updateData.getTaskId(), updateData.getTaskPriority()
    );

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskStatusUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskStatusUpdateData updateData = TaskStatusUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->updateTaskStatus(
        updateData.getTaskId(), updateData.getTaskStatus()
    );

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskAssigneeUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskAssigneeUpdateData updateData = TaskAssigneeUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->updateTaskExecutor(
        updateData.getTaskId(), updateData.getTaskAssigneeId()
    );

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskTagAdditionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskTagsUpdateData updateData = TaskTagsUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->addTagToTask(updateData.getTaskId(), updateData.getTagId());

    callback(drogon::HttpResponse::newHttpResponse());
}

void TaskTagDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const TaskTagsUpdateData updateData = TaskTagsUpdateData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getTaskService()->deleteTagFromTask(updateData.getTaskId(), updateData.getTagId());

    callback(drogon::HttpResponse::newHttpResponse());
}