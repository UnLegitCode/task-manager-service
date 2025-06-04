#include "../../include/dto/comment_dto.h"

CommentInfo::CommentInfo(
    std::string commentId, std::string commentContent
) : commentId(std::move(commentId)), commentContent(std::move(commentContent)) {}

std::string CommentInfo::getCommentId() {
    return commentId;
}

std::string CommentInfo::getCommentContent() {
    return commentContent;
}

std::unique_ptr<Json::Value> CommentInfo::toJson() const {
    Json::Value json;

    json["id"] = commentId;
    json["content"] = commentContent;

    return std::make_unique<Json::Value>(json);
}


CommentCreationData::CommentCreationData(
    std::string taskId, std::string commentContent
) : taskId(std::move(taskId)), commentContent(std::move(commentContent)) {}

std::string CommentCreationData::getTaskId() const {
    return taskId;
}

std::string CommentCreationData::getCommentContent() const {
    return commentContent;
}

CommentCreationData CommentCreationData::fromJson(const std::shared_ptr<Json::Value> &json) {
    const auto taskId = json.operator*()["task_id"].asString();
    const auto commentContent = json.operator*()["comment_content"].asString();

    return {taskId, commentContent};
}