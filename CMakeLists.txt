cmake_minimum_required(VERSION 3.20...3.28)
include(FetchContent)
project(chip_8)

message(STATUS "CMake ${CMAKE_VERSION}")
enable_testing()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB_RECURSE SOURCE_LIST "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_LIST "${CMAKE_CURRENT_LIST_DIR}/include/chip_8/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE_LIST} ${HEADER_LIST})
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    )

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    message("CMAKE SYSTEM IS: ${CMAKE_SYSTEM_NAME}")
    message("Compiling to WASM..." )

    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    target_link_libraries(${PROJECT_NAME} "-s USE_GLFW=3")
    target_link_libraries(${PROJECT_NAME} "-s WASM=1") #web assembly FTW
    target_link_libraries(${PROJECT_NAME} "-s USE_WEBGL2=1")
    #target_link_libraries(${PROJECT_NAME} "-s FULL_ES3=1")
    #target_link_libraries(${PROJECT_NAME} "-s FULL_ES2=1")
    #target_link_libraries(${PROJECT_NAME} "-s USE_FREETYPE=1")
    target_link_libraries(${PROJECT_NAME} "-s ALLOW_MEMORY_GROWTH=1")
    #target_link_libraries(${PROJECT_NAME} "--preload-file resources")
    #target_link_libraries(${PROJECT_NAME} "--use-preload-plugins")
    target_link_libraries(${PROJECT_NAME} "-o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/game.html")
    target_link_libraries(${PROJECT_NAME} "-s DEMANGLE_SUPPORT=1")
    target_compile_options(${PROJECT_NAME} PUBLIC "-O2") #creates the runtime resources
    target_link_libraries(${PROJECT_NAME} "-O2") #creates the runtime resources
    target_link_libraries(${PROJECT_NAME} glad) #creates the runtime resources
    target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src)

else()
    target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src)
    find_package(glfw3 3.3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE PUBLIC ${CMAKE_DL_LIBS} glfw glad)
endif()

