cmake_minimum_required(VERSION 3.15)
project(hello_boost)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/external/boost)
add_subdirectory(${BOOST_ROOT} external/boost_build)

find_package(Boost)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Could not find Boost!")
endif()

add_executable(hw19 main.cpp)

target_link_libraries(hw19 Boost::asio)