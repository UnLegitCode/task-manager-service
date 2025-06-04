#include "../../include/controllers/tag_controllers.h"
#include "../../include/instance_holder.h"
#include "../../include/dto/tag_dto.h"

void TagCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const auto tagCreationData = TagCreationData::fromJson(req->jsonObject());
    const auto tagId = InstanceHolder::getInstance()->getTagService()->createTag(
        tagCreationData.getProjectId(), tagCreationData.getTagName()
    );
    Json::Value responseBody;

    responseBody["tag_id"] = tagId;

    callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
}

void TagDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const auto tagId = req->jsonObject().operator*()["tag_id"].asString();

    InstanceHolder::getInstance()->getTagService()->deleteTag(tagId);

    callback(drogon::HttpResponse::newHttpResponse());
}