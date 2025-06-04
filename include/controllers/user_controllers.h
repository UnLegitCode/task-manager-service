#ifndef USER_CONTROLLERS_H
#define USER_CONTROLLERS_H

#include <drogon/HttpSimpleController.h>

class UserRegistrationController final : public drogon::HttpSimpleController<UserRegistrationController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/users/register", drogon::Post);
    PATH_LIST_END
};

class UserLoginController final : public drogon::HttpSimpleController<UserLoginController> {
public:
    void asyncHandleHttpRequest(
            const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr&)> &&callback
    ) override;

    PATH_LIST_BEGIN
        PATH_ADD("/users/login", drogon::Post);
    PATH_LIST_END
};

#endif //USER_CONTROLLERS_H