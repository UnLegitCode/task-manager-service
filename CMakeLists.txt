cmake_minimum_required(VERSION 3.30)
project(task_manager)

set(CMAKE_CXX_STANDARD 20)

find_package(Drogon REQUIRED)

find_package(jwt-cpp CONFIG REQUIRED)

add_executable(task_manager
        bcrypt/bcrypt.h
        bcrypt/node_blf.h
        bcrypt/openbsd.h
        bcrypt/bcrypt.cpp
        bcrypt/blowfish.cpp

        sqlite/sqlite3.h
        sqlite/sqlite3.c

        include/sql/sqlite3_handler.h
        src/sql/sqlite3_handler.cpp

        include/utilities/utility.h
        include/utilities/http_client.h
        src/utilities/utility.cpp
        src/utilities/http_client.cpp

        include/jwt/user_claims.h
        include/jwt/jwt_handler.h
        src/jwt/user_claims.cpp
        src/jwt/jwt_handler.cpp

        include/instance_holder.h
        src/instance_holder.cpp

        include/dto/user_dto.h
        include/dto/project_dto.h
        include/dto/task_dto.h
        include/dto/tag_dto.h
        include/dto/comment_dto.h
        src/dto/user_dto.cpp
        src/dto/project_dto.cpp
        src/dto/tag_dto.cpp
        src/dto/task_dto.cpp
        src/dto/comment_dto.cpp

        include/builder/builder.h
        include/builder/task_dto_builders.h
        include/builder/project_dto_builders.h
        src/builders/task_dto_builders.cpp
        src/builders/project_dto_builders.cpp

        include/repositories/user_repository.h
        include/repositories/project_repository.h
        include/repositories/task_repository.h
        include/repositories/tag_repository.h
        include/repositories/comment_repository.h
        src/repositories/user_repository.cpp
        src/repositories/comment_repository.cpp
        src/repositories/project_repository.cpp
        src/repositories/tag_repository.cpp
        src/repositories/task_repository.cpp

        include/services/notification_service.h
        include/services/user_service.h
        include/services/project_service.h
        include/services/task_service.h
        include/services/tag_service.h
        include/services/comment_service.h
        src/services/notification_service.cpp
        src/services/user_service.cpp
        src/services/project_service.cpp
        src/services/task_service.cpp
        src/services/tag_service.cpp
        src/services/comment_service.cpp

        include/controllers/user_controllers.h
        include/controllers/project_controllers.h
        include/controllers/task_controllers.h
        include/controllers/tag_controllers.h
        include/controllers/comment_controllers.h
        src/controllers/user_controllers.cpp
        src/controllers/project_controllers.cpp
        src/controllers/task_controllers.cpp
        src/controllers/tag_controllers.cpp
        src/controllers/comment_controllers.cpp

        main.cpp
)

target_link_libraries(task_manager
        PRIVATE
        Drogon::Drogon
        PRIVATE jwt-cpp::jwt-cpp
)