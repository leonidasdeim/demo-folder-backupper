cmake_minimum_required(VERSION 3.0.0)
project(FolderBackupper VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++2a -lstdc++") 

add_subdirectory(Utils)
add_subdirectory(FileProcessor)

add_executable(FolderBackupper main.cpp)

target_link_libraries(FolderBackupper PUBLIC Utils FileProcessor)
target_include_directories(FolderBackupper PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Utils/"
                          "${PROJECT_SOURCE_DIR}/FileProcessor/"
                          )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
