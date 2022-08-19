cmake_minimum_required(VERSION 3.16)

set(PROJ_NAME "vtk-test")
project(${PROJ_NAME})

set(vtk_prefix "D:/vtksoft/VTK-prefix")

include_directories(${vtk_prefix}/include/vtk-9.2/)

add_executable(${PROJ_NAME} main.cpp)

# target_link_libraries(${PROJ_NAME} ${vtk_prefix}/lib/*.lib)
target_link_libraries(${PROJ_NAME} ${vtk_prefix}/lib/*.lib)

add_subdirectory(src/MeshData)

target_link_libraries(${PROJ_NAME} target_lib_func)

add_subdirectory(src/BuildData)

target_link_libraries(${PROJ_NAME} target_lib_buildVTK)

add_subdirectory(src/FEA-lib)

target_link_libraries(${PROJ_NAME} target_lib_fea)


target_link_libraries(target_lib_fea PUBLIC
	 target_lib_func)
target_link_libraries(target_lib_buildVTK PUBLIC
	 target_lib_func)




