#include <drogon/HttpAppFramework.h>

#include "include/instance_holder.h"

int main() {
    InstanceHolder::initialize();

    std::thread([]() {
        drogon::app()
            .addListener("localhost", 12121)
            .run();
    }).detach();
}