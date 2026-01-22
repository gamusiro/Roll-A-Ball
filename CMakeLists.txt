cmake_minimum_required(VERSION 3.22.0)
project(Roll-A-Ball-GL)

# subdirectories
add_subdirectory(vendor/bullet)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/assimp)
add_subdirectory(vendor/freetype)

# project files
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/roll-a-ball/src/*.cpp
    ${CMAKE_SOURCE_DIR}/roll-a-ball/include/*.h
    ${CMAKE_SOURCE_DIR}/roll-a-ball/include/*.hpp
)

# build project
add_executable(${PROJECT_NAME} ${SOURCES})

# define
target_compile_definitions(${PROJECT_NAME} PUBLIC
    GLFW_INCLUDE_NONE
    GLM_ENABLE_EXPERIMENTAL
)

# include external
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/roll-a-ball/include
    ${CMAKE_SOURCE_DIR}/vendor/bullet/src
    ${CMAKE_SOURCE_DIR}/vendor/entt/src
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/vendor/assimp/include
    ${CMAKE_SOURCE_DIR}/vendor/freetype/include
    ${CMAKE_SOURCE_DIR}/vendor/utf/source
    ${CMAKE_SOURCE_DIR}/vendor/stb
    ${CMAKE_SOURCE_DIR}/build/vendor/assimp/include
)

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    EnTT
    glm
    GLAD
    assimp
    freetype
    BulletDynamics
    BulletCollision
    LinearMath
)

target_compile_options(${PROJECT_NAME} PUBLIC /FS)
target_compile_options(${PROJECT_NAME} PUBLIC "/utf-8")

# Asset Directory
set(ASSET_DIR ${CMAKE_SOURCE_DIR}/assets)

# Output Directory
set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets)

# Get asset files
file(GLOB_RECURSE ASSET_FILES
    ${ASSET_DIR}/*
)

# command copy
foreach(ASSET_FILE ${ASSET_FILES})
    # relative path
    file(RELATIVE_PATH RELATIVE_PATH ${ASSET_DIR} ${ASSET_FILE})
    set(DESTINATION_PATH "${OUTPUT_DIR}/${RELATIVE_PATH}")
    message(STATUS ${DESTINATION_PATH})

    # create dir & copy file
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        COMMAND ${CMAKE_COMMAND} -E copy ${ASSET_FILE} ${DESTINATION_PATH}
    )
endforeach()
