#ifndef TAG_CONTROLLERS_H
#define TAG_CONTROLLERS_H

#include <drogon/HttpSimpleController.h>

class TagCreationController final : public drogon::HttpSimpleController<TagCreationController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tags/create", drogon::Post);
    PATH_LIST_END
};

class TagDeletionController final : public drogon::HttpSimpleController<TagDeletionController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/tags/delete", drogon::Delete);
    PATH_LIST_END
};

#endif //TAG_CONTROLLERS_H