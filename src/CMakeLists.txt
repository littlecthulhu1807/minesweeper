file(GLOB_RECURSE SOURCES
    "*.cpp"
    "*.h"
    "*.cxx"
    "*.hpp"
)

# tell Cmake what files to compile into an executeable
add_executable(Minesweeper ${SOURCES})