#include "../../include/sql/sqlite3_handler.h"
#include <iostream>

SQLite3Handler::SQLite3Handler(const std::string& dbPath) {
    if (const int rc = sqlite3_open(dbPath.c_str(), &db); rc != SQLITE_OK) {
        const std::string errorMsg = "Cannot open database: " + std::string(sqlite3_errmsg(db));

        sqlite3_close(db);
        throw std::runtime_error(errorMsg);
    }
}

SQLite3Handler::~SQLite3Handler() {
    if (db) {
        sqlite3_close(db);
    }
}

void SQLite3Handler::checkError(const int rc, const std::string& errorMsg) const {
    if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
        throw std::runtime_error(errorMsg + ": " + sqlite3_errmsg(db));
    }
}

void SQLite3Handler::bindParameters(sqlite3_stmt* stmt, const std::map<std::string, std::string>& params) const {
    for (const auto&[key, value] : params) {
        const int idx = sqlite3_bind_parameter_index(stmt, key.c_str());

        if (idx == 0) {
            throw std::runtime_error("Parameter not found: " + key);
        }

        const int rc = sqlite3_bind_text(stmt, idx, value.c_str(), -1, SQLITE_TRANSIENT);

        checkError(rc, "Failed to bind parameter: " + key);
    }
}

void SQLite3Handler::update(const std::string& query) const {
    char* errMsg = nullptr;

    if (const int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg); rc != SQLITE_OK) {
        const std::string errorMsg = "Query (" + query + ") execution failed: " + std::string(errMsg);

        sqlite3_free(errMsg);

        throw std::runtime_error(errorMsg);
    }
}

void SQLite3Handler::update(const std::string& query,const std::map<std::string, std::string>& params) const {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    checkError(rc, "Failed to prepare statement");

    bindParameters(stmt, params);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        checkError(rc, "Failed to execute statement");
    }

    sqlite3_finalize(stmt);
}

std::vector<std::map<std::string, std::string>> SQLite3Handler::fetch(const std::string& query) const {
    std::vector<std::map<std::string, std::string>> result;
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    checkError(rc, "Failed to prepare statement");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::map<std::string, std::string> row;
        const int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; ++i) {
            const char* colName = sqlite3_column_name(stmt, i);

            if (const unsigned char* colValue = sqlite3_column_text(stmt, i); colName && colValue) {
                row[colName] = reinterpret_cast<const char*>(colValue);
            }
        }

        result.push_back(row);
    }

    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        checkError(rc, "Failed to fetch data");
    }

    sqlite3_finalize(stmt);

    return result;
}

std::vector<std::map<std::string, std::string>> SQLite3Handler::fetch(
    const std::string& query, const std::map<std::string, std::string>& params
) const {
    std::vector<std::map<std::string, std::string>> result;
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    checkError(rc, "Failed to prepare statement");

    bindParameters(stmt, params);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::map<std::string, std::string> row;
        const int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; ++i) {
            const char* colName = sqlite3_column_name(stmt, i);

            if (const unsigned char* colValue = sqlite3_column_text(stmt, i); colName && colValue) {
                row[colName] = reinterpret_cast<const char*>(colValue);
            }
        }

        result.push_back(row);
    }

    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        checkError(rc, "Failed to fetch data");
    }

    sqlite3_finalize(stmt);

    return result;
}