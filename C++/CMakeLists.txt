cmake_minimum_required(VERSION 2.8)
project(BroCar)
find_package( OpenCV REQUIRED )

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS})