cmake_minimum_required(VERSION 3.10)
project(MachineEpsilon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python REQUIRED COMPONENTS Interpreter Development)
message(STATUS "Python include dirs: ${Python_INCLUDE_DIRS}")
message(STATUS "Python libraries: ${Python_LIBRARIES}")

include_directories(
    ${Python_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_executable(${PROJECT_NAME}
    main.cpp
    includes/dword.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Python_LIBRARIES}
)