cmake_minimum_required(VERSION 2.8.3)
set(ev3dev_dir /home/rikilab/catkin_ws/src/ev3dev-lang-cpp)
set(ev3dev_lib ${ev3dev_dir}/build/libev3dev.a)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
project(hackev_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  hardware_interface
  transmission_interface
  controller_manager
  #ros_control
  #ros_controllers
)
# find_package(ev3dev-lang-cpp REQUIRED)

catkin_package(
 INCLUDE_DIRS include
  LIBRARIES $(PROJECT_NAME)
  CATKIN_DEPENDS roscpp hardware_interface transmission_interface controller_manager
  #DEPENDS ev3dev-lang-cpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
#  ${ev3dev_dir}
)

add_executable(hackev_control src/hackev_control.cpp src/hackev_hw.cpp)
# add_library(ev3dev-lang-cpp ev3dev.cpp)
target_link_libraries(
  hackev_control
  ${catkin_LIBRARIES}
#  ${ev3dev_lib}
  pthread
)

install(TARGETS hackev_control
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
