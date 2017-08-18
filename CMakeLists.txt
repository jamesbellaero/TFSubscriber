cmake_minimum_required (VERSION 3.5)
project (tfsubscriber)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  tf
)
catkin_package()
include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_subdirectory (${PROJECT_SOURCE_DIR}/src/libs/xbee_ansic_library/src/xbee)
add_executable(tfsubscriber src/tfsubscriber.cpp)
target_link_libraries (tfsubscriber XBee ${catkin_LIBRARIES})
