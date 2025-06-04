#ifndef USER_CLAIMS_H
#define USER_CLAIMS_H

#include <string>

class UserClaims {
    bool valid;
    std::string userId;

public:
    UserClaims(bool valid, std::string userId);
    ~UserClaims() = default;

    [[nodiscard]] bool isValid() const;
    [[nodiscard]] std::string getUserId() const;
};

#endif //USER_CLAIMS_H