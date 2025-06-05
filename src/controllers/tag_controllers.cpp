#include "../../include/controllers/tag_controllers.h"
#include "../../include/instance_holder.h"
#include "../../include/dto/tag_dto.h"
#include "../../include/utilities/utility.h"

void TagCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto tagCreationData = TagCreationData::fromJson(req->jsonObject());
        const auto tagId = InstanceHolder::getInstance()->getTagService()->createTag(
            userClaims.getUserId(), tagCreationData.getProjectId(), tagCreationData.getTagName()
        );
        Json::Value responseBody;

        responseBody["tag_id"] = tagId;

        callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void TagDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto tagId = req->jsonObject().operator*()["tag_id"].asString();

        InstanceHolder::getInstance()->getTagService()->deleteTag(userClaims.getUserId(), tagId);

        callback(drogon::HttpResponse::newHttpResponse());
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}