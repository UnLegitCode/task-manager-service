#ifndef SQLITE3_HANDLER_H
#define SQLITE3_HANDLER_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>

class SQLite3Handler {
    sqlite3* db{};

    void checkError(int rc, const std::string& errorMsg) const;
    void bindParameters(sqlite3_stmt* stmt, const std::map<std::string, std::string>& params) const;

public:
    explicit SQLite3Handler(const std::string& dbPath);
    ~SQLite3Handler();

    void update(const std::string &query) const;
    void update(const std::string& query, const std::map<std::string, std::string>& params) const;
    [[nodiscard]] std::vector<std::map<std::string, std::string>> fetch(const std::string& query) const;
    [[nodiscard]] std::vector<std::map<std::string, std::string>> fetch(
        const std::string& query, const std::map<std::string, std::string>& params
    ) const;
};

#endif // SQLITE3_HANDLER_H