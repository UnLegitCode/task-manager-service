#include "../../include/services/user_service.h"
#include "../../bcrypt/bcrypt.h"
#include "../../include/utilities/utility.h"

UserService::UserService(
    const UserRepository& userRepository, const JwtHandler& jwtHandler
) : userRepository(userRepository), jwtHandler(jwtHandler) {}

void UserService::registerUser(const std::string& username, const std::string &password) const {
    userRepository.insertUser(generateUUID(), username, bcrypt::generateHash(password, 6));
}

std::unique_ptr<std::string> UserService::verifyUser(const std::string& username, const std::string& password) const {
    const std::unique_ptr<std::string> actualPasswordHash = userRepository.getUserPasswordHash(username);

    if (!actualPasswordHash) {
        return {nullptr};
    }

    if (!bcrypt::validatePassword(password, *actualPasswordHash)) {
        return {nullptr};
    }

    return std::make_unique<std::string>(jwtHandler.generateToken(userRepository.getUserId(username)));
}
