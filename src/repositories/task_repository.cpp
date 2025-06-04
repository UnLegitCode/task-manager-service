#include "../../include/repositories/task_repository.h"

#include "../../include/builder/task_dto_builders.h"

TaskRepository::TaskRepository(
    SQLite3Handler& sqlHandler, CommentRepository& commentRepository
) : sqlHandler(sqlHandler), commentRepository(commentRepository) {
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `tasks`(`id` VARCHAR(36) PRIMARY KEY, `name` VARCHAR(32), `description` TEXT, `priority` TINYINT, `status` TINYINT, `assignee_id` VARCHAR(36));");
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `task_tags`(`task_id` VARCHAR(36), `tag_id` VARCHAR(36));");
    sqlHandler.update("CREATE TABLE IF NOT EXISTS `task_comments`(`task_id` VARCHAR(36), `comment_id` VARCHAR(36));");
}

void TaskRepository::insertTask(std::string projectId, std::string taskId, std::string taskName) const {
    sqlHandler.update("INSERT INTO `tasks`(`id`, `name`, `description`, `priority`, `status`, `assignee_id`) VALUES(:id, :name, :description, :priority, :status, :assignee_id);", {
        {":id", taskId},
        {":name", taskName},
        {":description", "NULL"},
        {":priority", "0"},
        {":status", "0"},
        {":assignee_id", "NULL"}
    });
    sqlHandler.update("INSERT INTO `project_tasks`(`project_id`, `task_id`) VALUES(:project_id, :task_id);", {
        {":project_id", projectId},
        {":task_id", taskId}
    });
}

void TaskRepository::deleteTask(std::string taskId) const {
    sqlHandler.update("DELETE FROM `tasks` WHERE `id`=:task_id;", {
        {":task_id", taskId}
    });
    sqlHandler.update("DELETE FROM `project_tasks` WHERE `task_id`=:task_id;", {
        {":task_id", taskId}
    });
}

void TaskRepository::updateTaskName(std::string taskId, std::string taskName) const {
    sqlHandler.update("UPDATE `tasks` SET `name`=:task_name WHERE `id`=:task_id;", {
        {":task_name", taskName},
        {":task_id", taskId}
    });
}

void TaskRepository::updateTaskDescription(std::string taskId, std::string taskDescription) const {
    sqlHandler.update("UPDATE `tasks` SET `description`=:task_description WHERE `id`=:task_id;", {
        {":task_description", taskDescription},
        {":task_id", taskId}
    });
}

void TaskRepository::updateTaskPriority(std::string taskId, const TaskPriority taskPriority) const {
    sqlHandler.update("UPDATE `tasks` SET `priority`=:task_priority WHERE `id`=:task_id;", {
        {":task_priority", std::to_string(taskPriority)},
        {":task_id", taskId}
    });
}

void TaskRepository::updateTaskStatus(std::string taskId, const TaskStatus taskStatus) const {
    sqlHandler.update("UPDATE `tasks` SET `status`=:task_status WHERE `id`=:task_id;", {
        {":task_status", std::to_string(taskStatus)},
        {":task_id", taskId}
    });
}

void TaskRepository::updateTaskAssignee(std::string taskId, std::string taskAssigneeId) const {
    sqlHandler.update("UPDATE `tasks` SET `assignee_id`=:task_assignee_id WHERE `id`=:task_id;", {
        {":task_assignee_id", taskAssigneeId},
        {":task_id", taskId}
    });
}

void TaskRepository::addTagToTask(std::string taskId, std::string tagId) const {
    sqlHandler.update("INSERT INTO `task_tags`(`task_id`, `tag_id`) VALUES(:task_id, :tag_id);", {
        {":task_id", taskId},
        {":tag_id", tagId}
    });
}

void TaskRepository::deleteTagFromTask(std::string taskId, std::string tagId) const {
    sqlHandler.update("DELETE FROM `task_tags` WHERE `task_id`=:task_id AND `tag_id`=:tag_id;", {
        {":task_id", taskId},
        {":tag_id", tagId}
    });
}

std::unique_ptr<TaskInfo> TaskRepository::getTaskInfo(std::string taskId) const {
    TaskInfoBuilder& builder = TaskInfoBuilder()
        .setId(taskId);
    const std::map<std::string, std::string> result = sqlHandler.fetch("SELECT `name`, `description`, `priority`, `status`, `assignee_id` FROM `tasks` WHERE `id`=:task_id LIMIT 1;", {
        {":task_id", taskId}
    }).front();
    builder
        .setName(result.at("name"))
        .setDescription(result.at("description"))
        .setAssigneeId(result.at("assignee_id"));

    const std::string rawTaskPriority = result.at("priority");
    const std::string rawTaskStatus = result.at("status");

    if (rawTaskPriority == "LOW") {
        builder.setPriority(LOW);
    } else if (rawTaskPriority == "MEDIUM") {
        builder.setPriority(MEDIUM);
    } else {
        builder.setPriority(HIGH);
    }

    if (rawTaskStatus == "TODO") {
        builder.setStatus(TODO);
    } else if (rawTaskStatus == "IN_PROGRESS") {
        builder.setStatus(IN_PROGRESS);
    } else {
        builder.setStatus(COMPLETED);
    }

    const std::vector<std::map<std::string, std::string>> tagsResult = sqlHandler.fetch("SELECT `tag_id` FROM `task_tags` WHERE `task_id`=:task_id;", {
        {":task_id", taskId}
    });

    for (auto& tagData : tagsResult) {
        builder.addTag(tagData.at("tag_id"));
    }

    for (const std::vector<CommentInfo> comments = commentRepository.getTaskComments(taskId); const auto & comment : comments) {
        builder.addComment(comment);
    }

    return builder.build();
}

std::vector<TaskInfo> TaskRepository::getProjectTasks(std::string projectId) const {
    const std::vector<std::map<std::string, std::string>> tasksResult = sqlHandler.fetch("SELECT task_id FROM project_tasks WHERE project_id=:project_id;", {
        {":project_id", projectId}
    });
    std::vector<TaskInfo> tasks;

    tasks.reserve(tasksResult.size());

    for (auto& taskData : tasksResult) {
        tasks.push_back(*getTaskInfo(taskData.at("task_id")));
    }

    return tasks;
}

std::string TaskRepository::getTaskName(std::string taskId) const {
    return sqlHandler.fetch("SELECT `name` FROM `tasks` WHERE `id`=:task_id LIMIT 1", {
        {":task_id", taskId}
    })[0].at("name");
}

std::string TaskRepository::getTaskProjectId(std::string taskId) const {
    return sqlHandler.fetch("SELECT `project_id` FROM `project_tasks` WHERE `task_id`=:task_id LIMIT 1;", {
        {":task_id", taskId}
    })[0].at("project_id");
}