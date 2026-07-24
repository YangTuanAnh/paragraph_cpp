cmake_minimum_required(VERSION 3.20)
project(backend_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(backend_tests
    main.cpp

    ../src/core/backend.cpp
    ../src/core/backend_areas.cpp
    ../src/core/backend_projects.cpp
    ../src/core/backend_tasks.cpp
    ../src/core/backend_resources.cpp
    # ../src/core/backend_graph.cpp
    ../src/core/utils.cpp
    
    ../src/lib/sqlite3.c
)

target_include_directories(backend_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)