#ifndef COMMENT_REPOSITORY_H
#define COMMENT_REPOSITORY_H

#include "../dto/comment_dto.h"
#include "../sql/sqlite3_handler.h"

class CommentRepository {
    SQLite3Handler& sqlHandler;
public:
    explicit CommentRepository(SQLite3Handler& sqlHandler);
    ~CommentRepository() = default;

    void insertComment(const std::string &taskId, const std::string &commentId, const std::string &commentContent) const;
    void deleteComment(const std::string &commentId) const;
    [[nodiscard]] std::vector<CommentInfo> getTaskComments(const std::string& taskId) const;
    [[nodiscard]] std::string getCommentTaskId(const std::string& commentId) const;
    [[nodiscard]] std::string getCommentContent(const std::string& commentId) const;
};

#endif //COMMENT_REPOSITORY_H