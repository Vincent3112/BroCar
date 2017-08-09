cmake_minimum_required(VERSION 2.8)
project(BroCar)
find_package( OpenCV REQUIRED )
find_package (Threads)

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(THIS_SRC )
add_executable(main main.cpp VideoGrabber.cpp UserControl.cpp)
target_link_libraries(main ${OpenCV_LIBS})
