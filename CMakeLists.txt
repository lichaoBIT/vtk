cmake_minimum_required(VERSION 3.16)

set(PROJ_NAME "vtk-test")
project(${PROJ_NAME})

set(vtk_prefix "D:/vtksoft/VTK-prefix")

include_directories(${vtk_prefix}/include/vtk-9.2/)
include_directories(./include/)

add_executable(${PROJ_NAME} main.cpp)

# target_link_libraries(${PROJ_NAME} ${vtk_prefix}/lib/*.lib)
target_link_libraries(${PROJ_NAME} ${vtk_prefix}/lib/*.lib)

# add_subdirectory(src/testfunctions)