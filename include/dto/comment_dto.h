#ifndef COMMENT_DTO_H
#define COMMENT_DTO_H

#include <string>
#include <json/value.h>

class CommentInfo {
    std::string commentId;
    std::string commentContent;
public:
    CommentInfo(std::string commentId, std::string commentContent);
    ~CommentInfo() = default;

    std::string getCommentId();
    std::string getCommentContent();

    [[nodiscard]] std::unique_ptr<Json::Value> toJson() const;
};

class CommentCreationData {
    std::string taskId;
    std::string commentContent;
public:
    CommentCreationData(std::string taskId, std::string commentContent);
    ~CommentCreationData() = default;

    [[nodiscard]] std::string getTaskId() const;
    [[nodiscard]] std::string getCommentContent() const;

    static CommentCreationData fromJson(const std::shared_ptr<Json::Value>& json);
};

#endif //COMMENT_DTO_H