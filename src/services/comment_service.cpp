#include "../../include/services/comment_service.h"
#include "../../include/utilities/utility.h"

CommentService::CommentService(
    CommentRepository& commentRepository, TaskRepository& taskRepository, NotificationService& notificationService
) : commentRepository(commentRepository), taskRepository(taskRepository), notificationService(notificationService) {}

std::string CommentService::createComment(
    const std::string& userId, const std::string& taskId, const std::string& commentContent
) const {
    std::string commentId = generateUUID();

    commentRepository.insertComment(taskId, commentId, commentContent);

    notificationService.notifyCommentCreation(userId, taskRepository.getTaskName(taskId), commentContent);

    return commentId;
}

void CommentService::deleteComment(const std::string& userId, const std::string& commentId) const {
    notificationService.notifyCommentDeletion(
        userId,
        taskRepository.getTaskName(commentRepository.getCommentTaskId(commentId)),
        commentRepository.getCommentContent(commentId)
    );

    commentRepository.deleteComment(commentId);
}