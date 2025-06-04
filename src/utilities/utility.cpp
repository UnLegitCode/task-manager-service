#include "../../include/utilities/utility.h"
#include <uuid/uuid.h>

#include "../../include/instance_holder.h"

std::string generateUUID() {
    uuid_t uuid;
    uuid_generate_random(uuid);

    char uuid_str[37];
    uuid_unparse(uuid, uuid_str);

    return uuid_str;
}

UserClaims extractClaims(const drogon::HttpRequestPtr &req) {
    const auto authHeader = req->getHeader("Authorization");

    if (authHeader.empty() || authHeader.find("Bearer ") != 0) {
        return {false, ""};
    }

    return InstanceHolder::getInstance()->getJwtHandler()->verifyToken(authHeader.substr(7));
}