#ifndef COMMENT_SERVICE_H
#define COMMENT_SERVICE_H

#include <string>

#include "notification_service.h"
#include "../repositories/comment_repository.h"
#include "../repositories/task_repository.h"

class CommentService {
    CommentRepository& commentRepository;
    TaskRepository& taskRepository;
    NotificationService& notificationService;
public:
    CommentService(
        CommentRepository& commentRepository, TaskRepository& taskRepository, NotificationService& notificationService
    );
    ~CommentService() = default;

    [[nodiscard]] std::string createComment(
        const std::string& userId, const std::string &taskId, const std::string &commentContent
    ) const;
    void deleteComment(const std::string& userId, const std::string &commentId) const;
};

#endif //COMMENT_SERVICE_H