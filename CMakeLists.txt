cmake_minimum_required(VERSION 2.8)

find_package(SWIG 2.0 REQUIRED)
include(${SWIG_USE_FILE})

find_package(PHPLibs REQUIRED)

set(INTERACTIVEBROKERS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/IBJts/cpp/PosixSocketClient ${CMAKE_CURRENT_SOURCE_DIR}/src/IBJts/cpp/Shared)
set(INTERACTIVEBROKERS_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/swig/interactiveBrokersAPI.cxx
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/IBJts/cpp/PosixSocketClient/EClientSocketBase.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/IBJts/cpp/PosixSocketClient/EPosixClientSocket.cpp)

include_directories(${INTERACTIVEBROKERS_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PHP_INCLUDE_DIRS})

set(CMAKE_SWIG_FLAGS "")
set(CMAKE_CXX_FLAGS "-DIB_USE_STD_STRING")


set_source_files_properties(swig/interactiveBrokersAPI.i PROPERTIES CPLUSPLUS on)
#set_source_files_properties(InteractiveBrokersAPI.i PROPERTIES SWIG_FLAGS "-includeall")

swig_add_module(interactiveBrokersAPI php swig/interactiveBrokersAPI.i ${INTERACTIVEBROKERS_SRCS})
swig_link_libraries(interactiveBrokersAPI ${PHP_LIBRARIES})
