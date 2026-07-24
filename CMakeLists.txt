cmake_minimum_required(VERSION 3.24)
project(Paragraph) # ##### RENAME ME! #####

# Workaround for CLang and RayLib's compound literals
# See: https://github.com/raysan5/raylib/issues/1343
set(CMAKE_CXX_STANDARD 17)
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# ===== Dependencies =====
include(FetchContent)

include(cmake/raylib.cmake)
include(cmake/imgui.cmake)
include(cmake/rlimgui.cmake)

include_directories(include)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# ===== Our Project =====
set(SOURCE_FILES
	src/main.cpp
    src/core/backend.cpp
    src/core/backend_areas.cpp
    src/core/backend_projects.cpp
    src/core/backend_tasks.cpp
    src/core/backend_resources.cpp
    src/core/backend_graph.cpp
    src/core/utils.cpp

    src/gui/menubar.cpp
    src/gui/router.cpp
    src/gui/page_projects.cpp
    src/gui/page_resources.cpp
    src/gui/page_areas.cpp
    src/gui/page_tasks.cpp
    src/gui/page_details/page_details.cpp
    src/gui/page_details/details_area.cpp
    src/gui/page_details/details_project.cpp
    src/gui/page_details/details_resource.cpp
    src/gui/page_details/details_task.cpp
    src/gui/page_workspace.cpp
    src/gui/page_graph.cpp
    src/gui/page_settings.cpp

    src/lib/imgui_stdlib.cpp
    src/lib/imnodes.cpp
    src/lib/imguidatechooser.cpp
    src/lib/sqlite3.c
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} data/resource.rc)

target_link_libraries(${PROJECT_NAME} rlimgui)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()


# Copy the data files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/data/
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/data/)

# installation
include(GNUInstallDirs)

install(TARGETS Paragraph
    RUNTIME DESTINATION .
)

install(DIRECTORY data
    DESTINATION .
)

set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_NAME "Paragraph")
set(CPACK_PACKAGE_VENDOR "Yang Tuan Anh")
set(CPACK_PACKAGE_VERSION "0.1.0")

include(CPack)