#ifndef COMMENT_CONTROLLERS_H
#define COMMENT_CONTROLLERS_H

#include <drogon/HttpSimpleController.h>

class CommentCreationController final : public drogon::HttpSimpleController<CommentCreationController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/comments/create", drogon::Post);
    PATH_LIST_END
};

class CommentDeletionController final : public drogon::HttpSimpleController<CommentDeletionController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/comments/delete", drogon::Delete);
    PATH_LIST_END
};

#endif //COMMENT_CONTROLLERS_H