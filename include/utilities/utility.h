#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <drogon/HttpRequest.h>

#include "../jwt/user_claims.h"

std::string generateUUID();

UserClaims extractClaims(const drogon::HttpRequestPtr &req);

#endif //UTILITY_H