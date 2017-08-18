cmake_minimum_required (VERSION 3.5)
project (TFSubscriber)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  time
  std_msgs
  message_generation
  geometry_msgs
  tf
)
catkin_package(
  CATKIN_DEPENDS message_runtime
)
include_directoris(
  ${catkin_INCLUDE_DIRS}
)
add_subdirectory (src/libs/xbee_ansic_library/src/xbee)
add_executable(tfsubscriber src/tfsubscriber.cpp)
target_link_libraries (tfsubscriber XBee)
