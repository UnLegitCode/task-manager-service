#include "../../include/controllers/project_controllers.h"
#include "../../include/instance_holder.h"
#include "../../include/utilities/utility.h"

void ProjectCreationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto projectName = req->jsonObject().operator*()["project_name"].asString();

        const std::string projectId = InstanceHolder::getInstance()->getProjectService()->createProject(
            userClaims.getUserId(), projectName
        );

        Json::Value responseBody;

        responseBody["project_id"] = projectId;

        callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void ProjectDeletionController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const auto projectId = req->jsonObject().operator*()["project_id"].asString();

    InstanceHolder::getInstance()->getProjectService()->deleteProject(projectId);

    callback(drogon::HttpResponse::newHttpResponse());
}

void ProjectListingController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    if (const auto userClaims = extractClaims(req); userClaims.isValid()) {
        const auto projectList = InstanceHolder::getInstance()->getProjectService()->listProjects(
            userClaims.getUserId()
        );

        Json::Value responseBody = Json::arrayValue;

        for (auto& projectMeta : projectList) {
            responseBody.append(*projectMeta.toJson());
        }

        callback(drogon::HttpResponse::newHttpJsonResponse(responseBody));
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k403Forbidden, drogon::CT_NONE));
    }
}

void ProjectInfoController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const auto projectId = req->jsonObject().operator*()["project_id"].asString();
    const auto projectInfo = InstanceHolder::getInstance()->getProjectService()->getProjectInfo(projectId);

    callback(drogon::HttpResponse::newHttpJsonResponse(*projectInfo->toJson()));
}

void ProjectMemberInvitationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr &)>&& callback
) {
    const ProjectMemberData memberData = ProjectMemberData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getProjectService()->inviteMember(
        memberData.getProjectId(), memberData.getMemberId()
    );

    callback(drogon::HttpResponse::newHttpResponse());
}

void ProjectMemberKickController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr &)>&& callback
) {
    const ProjectMemberData memberData = ProjectMemberData::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getProjectService()->kickMember(memberData.getProjectId(), memberData.getMemberId());

    callback(drogon::HttpResponse::newHttpResponse());
}
