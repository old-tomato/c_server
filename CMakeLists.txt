cmake_minimum_required(VERSION 3.8)
project(srs_c_server)

set(CMAKE_CXX_STANDARD 11)

set(LOCAL_DIR "/usr/local/lib")

link_directories(${LOCAL_DIR})

set(SOURCE_FILES main.cpp ServerContent.cpp ServerContent.h HttpHelper.cpp HttpHelper.h LoginController.cpp LoginController.h SqlHelper.cpp SqlHelper.h)
add_executable(srs_c_server ${SOURCE_FILES})
target_link_libraries(srs_c_server uv pthread mysqlclient cjson)