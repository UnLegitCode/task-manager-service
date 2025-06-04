#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>

#include "../sql/sqlite3_handler.h"

class UserRepository {
    SQLite3Handler& sqlHandler;
public:
    explicit UserRepository(SQLite3Handler& sqlHandler);
    ~UserRepository() = default;

    void insertUser(const std::string &userId, const std::string &username, const std::string &passwordHash) const;
    [[nodiscard]] std::string getUserId(const std::string &username) const;
    [[nodiscard]] std::unique_ptr<std::string> getUserPasswordHash(const std::string &username) const;
    [[nodiscard]] std::string getUsername(const std::string &userId) const;
};

#endif //USER_REPOSITORY_H