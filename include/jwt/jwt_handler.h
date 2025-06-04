#ifndef JWT_SERVICE_H
#define JWT_SERVICE_H

#include <string>
#include "user_claims.h"

class JwtHandler {
    std::string secret;
    std::chrono::duration<long> lifetime;

public:
    explicit JwtHandler(std::string secret, std::chrono::duration<long> lifetime);
    ~JwtHandler() = default;

    [[nodiscard]] std::string generateToken(std::string userId) const;
    [[nodiscard]] UserClaims verifyToken(const std::string &token) const;
};

#endif //JWT_SERVICE_H