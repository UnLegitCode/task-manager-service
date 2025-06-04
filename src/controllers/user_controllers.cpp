#include "../../include/controllers/user_controllers.h"
#include "../../include/dto/user_dto.h"
#include "../../include/instance_holder.h"

void UserRegistrationController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const UserCredentials userCredentials = UserCredentials::fromJson(req->jsonObject());

    InstanceHolder::getInstance()->getUserService()->registerUser(
        userCredentials.getUsername(), userCredentials.getPassword()
    );

    callback(drogon::HttpResponse::newHttpResponse());
}

void UserLoginController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {
    const UserCredentials userCredentials = UserCredentials::fromJson(req->jsonObject());

    const std::unique_ptr<std::string> tokenPtr = InstanceHolder::getInstance()->getUserService()->verifyUser(
        userCredentials.getUsername(), userCredentials.getPassword()
    );

    if (tokenPtr) {
        Json::Value response;

        response["token"] = *tokenPtr;

        callback(drogon::HttpResponse::newHttpJsonResponse(response));
    } else {
        callback(drogon::HttpResponse::newHttpResponse(drogon::k401Unauthorized, drogon::CT_NONE));
    }
}