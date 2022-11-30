# Install script for directory: /home/huy/catkin_ws/src/grasping_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/huy/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/action" TYPE FILE FILES
    "/home/huy/catkin_ws/src/grasping_msgs/action/FindGraspableObjects.action"
    "/home/huy/catkin_ws/src/grasping_msgs/action/GraspPlanning.action"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/msg" TYPE FILE FILES
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsAction.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsActionGoal.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsActionResult.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsActionFeedback.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsGoal.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsResult.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/FindGraspableObjectsFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/msg" TYPE FILE FILES
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningAction.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningActionGoal.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningActionResult.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningActionFeedback.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningGoal.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningResult.msg"
    "/home/huy/catkin_ws/devel/share/grasping_msgs/msg/GraspPlanningFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/msg" TYPE FILE FILES
    "/home/huy/catkin_ws/src/grasping_msgs/msg/GraspableObject.msg"
    "/home/huy/catkin_ws/src/grasping_msgs/msg/Object.msg"
    "/home/huy/catkin_ws/src/grasping_msgs/msg/ObjectProperty.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/cmake" TYPE FILE FILES "/home/huy/catkin_ws/build/grasping_msgs/catkin_generated/installspace/grasping_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/huy/catkin_ws/devel/include/grasping_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/huy/catkin_ws/devel/share/roseus/ros/grasping_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/huy/catkin_ws/devel/share/common-lisp/ros/grasping_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/huy/catkin_ws/devel/share/gennodejs/ros/grasping_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/huy/catkin_ws/devel/lib/python3/dist-packages/grasping_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/huy/catkin_ws/devel/lib/python3/dist-packages/grasping_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/huy/catkin_ws/build/grasping_msgs/catkin_generated/installspace/grasping_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/cmake" TYPE FILE FILES "/home/huy/catkin_ws/build/grasping_msgs/catkin_generated/installspace/grasping_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs/cmake" TYPE FILE FILES
    "/home/huy/catkin_ws/build/grasping_msgs/catkin_generated/installspace/grasping_msgsConfig.cmake"
    "/home/huy/catkin_ws/build/grasping_msgs/catkin_generated/installspace/grasping_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grasping_msgs" TYPE FILE FILES "/home/huy/catkin_ws/src/grasping_msgs/package.xml")
endif()

