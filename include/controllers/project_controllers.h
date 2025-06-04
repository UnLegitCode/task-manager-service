#ifndef PROJECT_CONTROLLERS_H
#define PROJECT_CONTROLLERS_H

#include <drogon/HttpSimpleController.h>

class ProjectCreationController final : public drogon::HttpSimpleController<ProjectCreationController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/projects/create", drogon::Post);
    PATH_LIST_END
};

class ProjectDeletionController final : public drogon::HttpSimpleController<ProjectDeletionController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/projects/delete", drogon::Delete);
    PATH_LIST_END
};

class ProjectListingController final : public drogon::HttpSimpleController<ProjectListingController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/projects/list", drogon::Get);
    PATH_LIST_END
};

class ProjectInfoController final : public drogon::HttpSimpleController<ProjectInfoController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/projects/info", drogon::Get);
    PATH_LIST_END
};

class ProjectMemberInvitationController final : public drogon::HttpSimpleController<ProjectMemberInvitationController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/projects/invite", drogon::Post);
    PATH_LIST_END
};

class ProjectMemberKickController final : public drogon::HttpSimpleController<ProjectMemberKickController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/projects/kick", drogon::Post);
    PATH_LIST_END
};

#endif //PROJECT_CONTROLLERS_H