#include "../../include/controllers/comment_controllers.h"
#include "../../include/instance_holder.h"
#include "../../include/dto/comment_dto.h"
#include "../../include/utilities/utility.h"

void CommentCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto tagCreationData = CommentCreationData::fromJson(req->jsonObject());
        const auto commentId = InstanceHolder::getInstance()->getCommentService()->createComment(
             userClaims.getUserId(), tagCreationData.getTaskId(), tagCreationData.getCommentContent()
        );
        Json::Value responseBody;

        responseBody["comment_id"] = commentId;

        callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void CommentDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto commentId = req->jsonObject().operator*()["comment_id"].asString();

        InstanceHolder::getInstance()->getCommentService()->deleteComment(userClaims.getUserId(), commentId);

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}