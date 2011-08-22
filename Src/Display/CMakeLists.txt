cmake_minimum_required(VERSION 2.8)
PROJECT (Display)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

add_library(simplereader SimpleReader.cpp SimpleReader.h)

add_executable(${PROJECT_NAME} mainprogram.cpp simplereader)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CORELIBS} -lglut32 -lglu32 -lopengl32 simplereader)
     
