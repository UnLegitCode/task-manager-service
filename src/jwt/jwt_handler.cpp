#include <jwt-cpp/jwt.h>

#include "../../include/jwt/jwt_handler.h"

JwtHandler::JwtHandler(
    std::string secret, const std::chrono::duration<long> lifetime
) : secret(std::move(secret)), lifetime(lifetime) {}


std::string JwtHandler::generateToken(std::string userId) const {
    return jwt::create()
        .set_issuer("task_manager_service")
        .set_type("JWT")
        .set_payload_claim("user_id", jwt::claim(std::move(userId)))
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + lifetime)
        .sign(jwt::algorithm::hs256{secret});
}

UserClaims JwtHandler::verifyToken(const std::string& token) const {
    const auto decodedToken = jwt::decode(token);
    const auto verifier = jwt::verify()
        .allow_algorithm(jwt::algorithm::hs256{secret})
        .with_issuer("task_manager_service");

    try {
        verifier.verify(decodedToken);
    } catch (const jwt::error::token_verification_exception&) {
        return {false, ""};
    }

    std::string userId = decodedToken.get_payload_claim("user_id").as_string();

    return {true, userId};
}
