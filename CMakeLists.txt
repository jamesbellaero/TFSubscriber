cmake_minimum_required (VERSION 3.5)
project (TFSubscriber)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  time
  std_msgs
  geometry_msgs
  tf
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_subdirectory (src/libs/xbee_ansic_library/src/xbee)
add_executable(tfsubscriber src/tfsubscriber.cpp)
target_link_libraries (tfsubscriber XBee ${catkin_LIBRARIES})
