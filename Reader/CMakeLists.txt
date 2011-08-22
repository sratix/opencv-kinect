cmake_minimum_required(VERSION 2.8)
PROJECT (bvhReader)
FIND_PACKAGE( OpenCV REQUIRED )

include_directories(${OpenCV_Dir}/include ${OpenCV_Dir}/include/opencv)
link_directories(${OpenCV_Dir}/lib)

add_library(reader reader.cpp reader.h)
add_library(pose pose.cpp pose.h)
add_library(structure structure.cpp structure.h)
add_library(substructure substructure.cpp substructure.h)
add_library(framebvh framebvh.cpp framebvh.h)
add_executable(${PROJECT_NAME} mainprogram.cpp reader pose structure substructure framebvh)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${OpenCV_LIBS} reader pose structure substructure framebvh)
     
