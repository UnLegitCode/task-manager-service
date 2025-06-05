#include "../include/instance_holder.h"
#include "../include/sql/sqlite3_handler.h"
#include "../include/utilities/http_client.h"

std::shared_ptr<InstanceHolder> InstanceHolder::instance = nullptr;

InstanceHolder::InstanceHolder() :
    sqlHandler(SQLite3Handler("../database.db")),

    userRepository(UserRepository(sqlHandler)),
    commentRepository(CommentRepository(sqlHandler)),
    taskRepository(TaskRepository(sqlHandler, commentRepository)),
    tagRepository(TagRepository(sqlHandler)),
    projectRepository(ProjectRepository(sqlHandler, taskRepository, tagRepository)),

    jwtHandler(JwtHandler("secret_key", std::chrono::minutes(30))),

    notificationService(NotificationService("http://localhost:12122")),
    userService(UserService(userRepository, jwtHandler)),
    projectService(ProjectService(projectRepository, userRepository, notificationService)),
    taskService(TaskService(taskRepository, projectRepository, tagRepository, userRepository, notificationService)),
    tagService(TagService(tagRepository, projectRepository, notificationService)),
    commentService(CommentService(commentRepository, taskRepository, notificationService)
) {}

std::unique_ptr<UserRepository> InstanceHolder::getUserRepository() {
    return std::make_unique<UserRepository>(userRepository);
}

std::unique_ptr<CommentRepository> InstanceHolder::getCommentRepository() {
    return std::make_unique<CommentRepository>(commentRepository);
}

std::unique_ptr<TaskRepository> InstanceHolder::getTaskRepository() {
    return std::make_unique<TaskRepository>(taskRepository);
}

std::unique_ptr<TagRepository> InstanceHolder::getTagRepository() {
    return std::make_unique<TagRepository>(tagRepository);
}

std::unique_ptr<ProjectRepository> InstanceHolder::getProjectRepository() {
    return std::make_unique<ProjectRepository>(projectRepository);
}

std::unique_ptr<JwtHandler> InstanceHolder::getJwtHandler() {
    return std::make_unique<JwtHandler>(jwtHandler);
}

std::unique_ptr<UserService> InstanceHolder::getUserService() {
    return std::make_unique<UserService>(userService);
}

std::unique_ptr<ProjectService> InstanceHolder::getProjectService() {
    return std::make_unique<ProjectService>(projectService);
}

std::unique_ptr<TaskService> InstanceHolder::getTaskService() {
    return std::make_unique<TaskService>(taskService);
}

std::unique_ptr<TagService> InstanceHolder::getTagService() {
    return std::make_unique<TagService>(tagService);
}

std::unique_ptr<CommentService> InstanceHolder::getCommentService() {
    return std::make_unique<CommentService>(commentService);
}