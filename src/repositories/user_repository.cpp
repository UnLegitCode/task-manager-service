#include "../../include/repositories/user_repository.h"

#include <iostream>
#include <ostream>

UserRepository::UserRepository(SQLite3Handler& sqlHandler) : sqlHandler(sqlHandler) {
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `users`(`id` VARCHAR(36) PRIMARY KEY, `username` VARCHAR(32) UNIQUE, `password_hash` VARCHAR(72));");
}

void UserRepository::insertUser(
    const std::string& userId, const std::string& username, const std::string& passwordHash
) const {
    sqlHandler.update("INSERT INTO `users`(`id`,`username`,`password_hash`) VALUES(:id, :username, :password_hash);", {
        {":id", userId},
        {":username", username},
        {":password_hash", passwordHash}
    });
}

std::string UserRepository::getUserId(const std::string& username) const {
    const std::vector<std::map<std::string, std::string>> result = sqlHandler.fetch(
        "SELECT `id` FROM `users` WHERE `username`=:username LIMIT 1;", {
            {":username", username}
        }
    );

    if (result.empty()) {
        throw std::runtime_error("Failed to find user id for " + username);
    }

    return result.front().at("id");
}

std::unique_ptr<std::string> UserRepository::getUserPasswordHash(const std::string& username) const {
    const std::vector<std::map<std::string, std::string>> result = sqlHandler.fetch(
        "SELECT `password_hash` FROM `users` WHERE `username`=:username LIMIT 1;", {
            {":username", username}
        }
    );

    if (result.empty()) {
        return nullptr;
    }

    return std::make_unique<std::string>(result.front().at("password_hash"));
}

std::string UserRepository::getUsername(const std::string &userId) const {
    return sqlHandler.fetch("SELECT `username` FROM `users` WHERE `id`=:id LIMIT 1;", {
        {":id", userId}
    })[0].at("username");
}