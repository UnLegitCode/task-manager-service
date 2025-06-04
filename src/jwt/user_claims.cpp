#include "../../include/jwt/user_claims.h"

UserClaims::UserClaims(const bool valid, std::string userId) : valid(valid), userId(std::move(userId)) {}

bool UserClaims::isValid() const {
    return valid;
}

std::string UserClaims::getUserId() const {
    return userId;
}