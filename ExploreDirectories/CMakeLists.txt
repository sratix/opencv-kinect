cmake_minimum_required(VERSION 2.8)
PROJECT (exploreTest)
include_directories({PROJECT_NAME}/dependencies)
link_directories(${OpenCV_Dir}/lib)
add_library(explore explore.cpp explore.h)
add_library(simplewriter simplewriter.cpp simplewriter.h)
add_executable(${PROJECT_NAME} mainprogram.cpp explore simplewriter)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} explore simplewriter)
     
