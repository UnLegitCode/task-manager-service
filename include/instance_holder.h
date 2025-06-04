#ifndef INSTANCE_HOLDER_H
#define INSTANCE_HOLDER_H

#include <mutex>

#include "repositories/user_repository.h"
#include "repositories/project_repository.h"
#include "repositories/task_repository.h"
#include "repositories/tag_repository.h"
#include "repositories/comment_repository.h"

#include "services/user_service.h"
#include "services/project_service.h"
#include "services/task_service.h"
#include "services/tag_service.h"
#include "services/comment_service.h"
#include "services/notification_service.h"
#include "sql/sqlite3_handler.h"
#include "utilities/http_client.h"

class InstanceHolder {
    SQLite3Handler sqlHandler;

    UserRepository userRepository;
    CommentRepository commentRepository;
    TaskRepository taskRepository;
    TagRepository tagRepository;
    ProjectRepository projectRepository;

    JwtHandler jwtHandler;

    NotificationService notificationService;
    UserService userService;
    ProjectService projectService;
    TaskService taskService;
    TagService tagService;
    CommentService commentService;

    static std::shared_ptr<InstanceHolder> instance;
public:
    InstanceHolder();
    ~InstanceHolder() = default;
    InstanceHolder(const InstanceHolder&) = delete;
    InstanceHolder& operator=(const InstanceHolder&) = delete;

    static void initialize() {
        instance = std::make_shared<InstanceHolder>();
    }

    static std::shared_ptr<InstanceHolder> getInstance() {
        return instance;
    }

    std::unique_ptr<UserRepository> getUserRepository();
    std::unique_ptr<CommentRepository> getCommentRepository();
    std::unique_ptr<TaskRepository> getTaskRepository();
    std::unique_ptr<TagRepository> getTagRepository();
    std::unique_ptr<ProjectRepository> getProjectRepository();

    std::unique_ptr<JwtHandler> getJwtHandler();

    std::unique_ptr<UserService> getUserService();
    std::unique_ptr<ProjectService> getProjectService();
    std::unique_ptr<TaskService> getTaskService();
    std::unique_ptr<TagService> getTagService();
    std::unique_ptr<CommentService> getCommentService();
};

#endif //INSTANCE_HOLDER_H