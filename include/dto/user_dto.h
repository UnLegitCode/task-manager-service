#ifndef USER_DTO_H
#define USER_DTO_H

#include <string>
#include <json/value.h>

class UserCredentials {
    std::string username;
    std::string password;

public:
    UserCredentials(std::string username, std::string password);
    ~UserCredentials() = default;

    [[nodiscard]] std::string getUsername() const;
    [[nodiscard]] std::string getPassword() const;

    static UserCredentials fromJson(const std::shared_ptr<Json::Value>& json);
};

class UserInfo {
    std::string id;
    std::string username;

public:
    UserInfo(std::string id, std::string username);
    ~UserInfo() = default;

    [[nodiscard]] std::string getId() const;
    [[nodiscard]] std::string getUsername() const;

    [[nodiscard]] std::unique_ptr<Json::Value> toJson() const;
};

#endif //USER_DTO_H