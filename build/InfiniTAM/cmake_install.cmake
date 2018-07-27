# Install script for directory: /home/localadmin/Telepresence_Robot_InfiniTAM/src/InfiniTAM

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/localadmin/Telepresence_Robot_InfiniTAM/install")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/catkin_generated/installspace/InfiniTAM.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/InfiniTAM/cmake" TYPE FILE FILES
    "/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/catkin_generated/installspace/InfiniTAMConfig.cmake"
    "/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/catkin_generated/installspace/InfiniTAMConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/InfiniTAM" TYPE FILE FILES "/home/localadmin/Telepresence_Robot_InfiniTAM/src/InfiniTAM/package.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/InfiniTAM/Apps/cmake_install.cmake")
  include("/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/InfiniTAM/FernRelocLib/cmake_install.cmake")
  include("/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/InfiniTAM/InputSource/cmake_install.cmake")
  include("/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/InfiniTAM/ITMLib/cmake_install.cmake")
  include("/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/InfiniTAM/MiniSlamGraphLib/cmake_install.cmake")
  include("/home/localadmin/Telepresence_Robot_InfiniTAM/build/InfiniTAM/InfiniTAM/ORUtils/cmake_install.cmake")

endif()

