add_library(FileProcessor FileProcessor.cpp)

link_libraries(FileProcessor PUBLIC Utils)
include_directories(FileProcessor PUBLIC
                    "${PROJECT_SOURCE_DIR}/Utils/"
                    )
                          