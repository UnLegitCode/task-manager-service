#ifndef TAG_REPOSITORY_H
#define TAG_REPOSITORY_H

#include "../dto/tag_dto.h"
#include "../sql/sqlite3_handler.h"

class TagRepository {
    SQLite3Handler& sqlHandler;
public:
    explicit TagRepository(SQLite3Handler& sqlHandler);
    ~TagRepository() = default;

    void insertTag(const std::string& projectId, const std::string& tagId, const std::string& tagName) const;
    void deleteTag(const std::string& tagId) const;
    [[nodiscard]] std::vector<TagInfo> getProjectTasks(const std::string& projectId) const;
    [[nodiscard]] std::string getTagName(const std::string& tagId) const;
    [[nodiscard]] std::string getTagProjectId(std::string tagId) const;
};

#endif //TAG_REPOSITORY_H