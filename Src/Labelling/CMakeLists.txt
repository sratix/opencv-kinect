cmake_minimum_required(VERSION 2.8)
PROJECT (LabellingPipeline)
add_library(simplereader SimpleReader.cpp SimpleReader.h)
add_library(bodypart BodyPart.cpp BodyPart.h)
add_library(mesh mesh.cpp mesh.h)
add_library(simplewriter SimpleWriter.cpp SimpleWriter.h)
add_executable(${PROJECT_NAME} mainprogram.cpp simplereader mesh bodypart simplewriter)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} mesh simplereader bodypart simplewriter)
     
