#include "../../include/repositories/comment_repository.h"

CommentRepository::CommentRepository(SQLite3Handler& sqlHandler) : sqlHandler(sqlHandler) {
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `comments`(`id` VARCHAR(36) PRIMARY KEY, `content` TEXT);");
}

void CommentRepository::insertComment(
    const std::string& taskId, const std::string& commentId, const std::string& commentContent
) const {
    sqlHandler.update("INSERT INTO `comments`(`id`, `content`) VALUES(:id, :content);", {
        {":id", commentId},
        {":content", commentContent}
    });
    sqlHandler.update("INSERT INTO `task_comments`(`task_id`, `comment_id`) VALUES(:task_id, :comment_id);", {
        {":task_id", taskId},
        {":comment_id", commentId}
    });
}

void CommentRepository::deleteComment(const std::string& commentId) const {
    sqlHandler.update("DELETE FROM `comments` WHERE `id`=:comment_id;", {
        {":comment_id", commentId}
    });
    sqlHandler.update("DELETE FROM `task_comments` WHERE `comment_id`=:comment_id;", {
        {":comment_id", commentId}
    });
}

std::vector<CommentInfo> CommentRepository::getTaskComments(const std::string &taskId) const {
    std::vector<std::map<std::string, std::string>> commentsResult = sqlHandler.fetch("SELECT tc.comment_id, c.content FROM task_comments tc INNER JOIN comments c ON tc.comment_id=c.id WHERE tc.task_id=:task_id;", {
        {":task_id", taskId}
    });
    std::vector<CommentInfo> comments;

    comments.reserve(commentsResult.size());

    for (auto& commentData : commentsResult) {
        comments.emplace_back(commentData.at("tc.comment_id"), commentData.at("c.content"));
    }

    return comments;
}

std::string CommentRepository::getCommentTaskId(const std::string &commentId) const {
    return sqlHandler.fetch("SELECT `task_id` FROM `task_comments` WHERE `comment_id`=:comment_id LIMIT 1;", {
        {":comment_id", commentId}
    })[0].at("task_id");
}

std::string CommentRepository::getCommentContent(const std::string &commentId) const {
    return sqlHandler.fetch("SELECT `content` FROM `comments` WHERE `id`=:comment_id LIMIT 1;", {
        {":comment_id", commentId}
    })[0].at("content");
}