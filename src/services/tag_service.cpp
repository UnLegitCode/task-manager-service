#include "../../include/services/tag_service.h"
#include "../../include/utilities/utility.h"

TagService::TagService(
    TagRepository& tagRepository, ProjectRepository& projectRepository, NotificationService& notificationService
) : tagRepository(tagRepository), projectRepository(projectRepository), notificationService(notificationService) {}

std::string TagService::createTag(
    const std::string& userId, const std::string& projectId, const std::string& tagName
) const {
    std::string tagId = generateUUID();

    tagRepository.insertTag(projectId, tagId, tagName);

    notificationService.notifyTagCreation(userId, projectRepository.getProjectName(projectId), tagName);

    return tagId;
}

void TagService::deleteTag(const std::string& userId, const std::string& tagId) const {
    tagRepository.deleteTag(tagId);

    notificationService.notifyTagCreation(
        userId,
        projectRepository.getProjectName(tagRepository.getTagProjectId(tagId)),
        tagRepository.getTagName(tagId)
    );
}