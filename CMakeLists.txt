# define minimum required version of CMake
cmake_minimum_required(VERSION 3.31) 

# define the project by giving it a name and set the language and project version
project(Minesweeper
    LANGUAGES CXX 
    VERSION 1.0
)
set(CMAKE_CXX_STANDARD 20) #set language standart for c++

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/bin
)

# add a directory to look for additional CMake files
add_subdirectory(src)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

# Copy DLLs needed for runtime on Windows
if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET financeCalc POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:financeCalc>)
  endif()
endif()



#Build the cmake files and directories:
#go into the -build directory
#run "cmake ../projectname-project"

#build the executeable:
#cmake --build .

#to turn off shared Lib building:
# cmake -DBUILD_SHARED_LIBS=OFF -S . -B out