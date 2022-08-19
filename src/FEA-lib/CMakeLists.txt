add_library(target_lib_fea FEA.cpp elements.cpp nodes.cpp)
target_include_directories(target_lib_fea PUBLIC include)