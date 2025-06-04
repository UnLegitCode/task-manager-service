#include "../../include/controllers/comment_controllers.h"
#include "../../include/instance_holder.h"
#include "../../include/dto/comment_dto.h"

void CommentCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const auto tagCreationData = CommentCreationData::fromJson(req->jsonObject());
    const auto commentId = InstanceHolder::getInstance()->getCommentService()->createComment(
        tagCreationData.getTaskId(), tagCreationData.getCommentContent()
    );
    Json::Value responseBody;

    responseBody["comment_id"] = commentId;

    callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
}

void CommentDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
    ) {
    const auto commentId = req->jsonObject().operator*()["comment_id"].asString();

    InstanceHolder::getInstance()->getCommentService()->deleteComment(commentId);

    callback(drogon::HttpResponse::newHttpResponse());
}