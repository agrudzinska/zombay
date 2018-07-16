cmake_minimum_required(VERSION 3.9)
#require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(zombay)

#Setup Directories
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
#Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#Add external dependencies
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

###zombay
file(GLOB_RECURSE SOURCES zombay/*.cpp zombay/*.h)
add_executable(zombay ${SOURCES})
target_include_directories(zombay PRIVATE ${SFML_INCS})
target_link_libraries(zombay sfml-graphics)
