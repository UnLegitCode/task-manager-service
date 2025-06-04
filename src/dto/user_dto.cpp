#include "../../include/dto/user_dto.h"

UserCredentials::UserCredentials(
    std::string username, std::string password
) : username(std::move(username)), password(std::move(password)) {}

std::string UserCredentials::getUsername() const {
    return username;
}

std::string UserCredentials::getPassword() const {
    return password;
}

UserCredentials UserCredentials::fromJson(const std::shared_ptr<Json::Value>& json) {
    const auto username = json.operator*()["username"].asString();
    const auto password = json.operator*()["password"].asString();

    return {username, password};
}


UserInfo::UserInfo(std::string id, std::string username) : id(std::move(id)), username(std::move(username)) {}

std::string UserInfo::getId() const {
    return id;
}

std::string UserInfo::getUsername() const {
    return username;
}

std::unique_ptr<Json::Value> UserInfo::toJson() const {
    Json::Value json;

    json["id"] = id;
    json["username"] = username;

    return std::make_unique<Json::Value>(json);
}