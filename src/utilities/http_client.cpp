#include "../../include/utilities/http_client.h"

HttpClient::HttpClient(const std::string& baseUrl) : client(drogon::HttpClient::newHttpClient(baseUrl)) {}

void HttpClient::sendAsyncRequest(
    const drogon::HttpMethod method, const std::string &path, const std::string &jsonBody
) const {
    const auto request = drogon::HttpRequest::newHttpRequest();

    request->setMethod(method);
    request->setPath(path);

    if (!jsonBody.empty()) {
        request->setBody(jsonBody);
        request->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    }

    client->sendRequest(request, [](drogon::ReqResult result, const drogon::HttpResponsePtr &resp) {
        if (result != drogon::ReqResult::Ok || !resp) {
            std::cerr << "⚠️ Request failed! Error: ";

            if (result == drogon::ReqResult::BadResponse) {
                std::cerr << "Bad response from server";
            } else if (result == drogon::ReqResult::Timeout) {
                std::cerr << "Timeout";
            } else {
                std::cerr << "Unknown error";
            }

            std::cerr << std::endl;
        }
    });
}

void HttpClient::sendAsyncRequest(
    const drogon::HttpMethod method, const std::string &path, const Json::Value& jsonBody
) const {
    sendAsyncRequest(method, path, jsonBody.toStyledString());
}