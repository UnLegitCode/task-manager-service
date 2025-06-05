#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <string>

class HttpClient {
    std::shared_ptr<drogon::HttpClient> client;
public:
    explicit HttpClient(const std::string& baseUrl);
    ~HttpClient() = default;

    void sendAsyncRequest(
        drogon::HttpMethod method, const std::string& path, const std::string& jsonBody = ""
    ) const;

    void sendAsyncRequest(drogon::HttpMethod method, const std::string& path, const Json::Value& jsonBody) const;
};

#endif //HTTP_CLIENT_H