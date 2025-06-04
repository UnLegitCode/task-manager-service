#ifndef TAG_SERVICE_H
#define TAG_SERVICE_H

#include <string>

#include "notification_service.h"
#include "../repositories/project_repository.h"
#include "../repositories/tag_repository.h"

class TagService {
    TagRepository& tagRepository;
    ProjectRepository& projectRepository;
    NotificationService& notificationService;
public:
    TagService(TagRepository& tagRepository, ProjectRepository& projectRepository, NotificationService& notificationService);
    ~TagService() = default;

    [[nodiscard]] std::string createTag(
        const std::string& userId, const std::string &projectId, const std::string &tagName
    ) const;
    void deleteTag(const std::string& userId, const std::string &tagId) const;
};

#endif //TAG_SERVICE_H