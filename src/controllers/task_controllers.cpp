#include "../../include/controllers/task_controllers.h"
#include "../../include/instance_holder.h"
#include "../../include/dto/task_dto.h"
#include "../../include/utilities/utility.h"

void TaskCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskCreationData taskCreationData = TaskCreationData::fromJson(req->jsonObject());
        const std::string taskId = InstanceHolder::getInstance()->getTaskService()->createTask(
            userClaims.getUserId(), taskCreationData.getProjectId(), taskCreationData.getTaskName()
        );
        Json::Value responseBody;

        responseBody["task_id"] = taskId;

        callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto taskId = req->getJsonObject().operator*()["task_id"].asString();

        InstanceHolder::getInstance()->getTaskService()->deleteTask(userClaims.getUserId(), taskId);

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskNameUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskNameUpdateData updateData = TaskNameUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->updateTaskName(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTaskName()
        );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskDescriptionUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskDescriptionUpdateData updateData = TaskDescriptionUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->updateTaskDescription(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTaskDescription()
        );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskPriorityUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskPriorityUpdateData updateData = TaskPriorityUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->updateTaskPriority(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTaskPriority()
        );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskStatusUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskStatusUpdateData updateData = TaskStatusUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->updateTaskStatus(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTaskStatus()
        );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskAssigneeUpdateController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskAssigneeUpdateData updateData = TaskAssigneeUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->updateTaskAssignee(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTaskAssigneeId()
        );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskTagAdditionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskTagsUpdateData updateData = TaskTagsUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->addTagToTask(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTagId()
       );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TaskTagDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const TaskTagsUpdateData updateData = TaskTagsUpdateData::fromJson(req->jsonObject());

        InstanceHolder::getInstance()->getTaskService()->deleteTagFromTask(
            userClaims.getUserId(), updateData.getTaskId(), updateData.getTagId()
        );

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}