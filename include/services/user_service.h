#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <string>

#include "../jwt/jwt_handler.h"
#include "../repositories/user_repository.h"

class UserService {
    UserRepository userRepository;
    JwtHandler jwtHandler;

public:
    UserService(const UserRepository& userRepository, const JwtHandler& jwtHandler);
    ~UserService() = default;

    void registerUser(const std::string &username, const std::string &password) const;
    std::unique_ptr<std::string> verifyUser(const std::string& username, const std::string& password) const;
};

#endif //USER_SERVICE_H