# Install script for directory: /home/antonyhwang/infinitam_ws/src/InfiniTAM

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/antonyhwang/infinitam_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/antonyhwang/infinitam_ws/build/InfiniTAM/catkin_generated/installspace/InfiniTAM.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/InfiniTAM/cmake" TYPE FILE FILES
    "/home/antonyhwang/infinitam_ws/build/InfiniTAM/catkin_generated/installspace/InfiniTAMConfig.cmake"
    "/home/antonyhwang/infinitam_ws/build/InfiniTAM/catkin_generated/installspace/InfiniTAMConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/InfiniTAM" TYPE FILE FILES "/home/antonyhwang/infinitam_ws/src/InfiniTAM/package.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/antonyhwang/infinitam_ws/build/InfiniTAM/InfiniTAM/Apps/cmake_install.cmake")
  include("/home/antonyhwang/infinitam_ws/build/InfiniTAM/InfiniTAM/FernRelocLib/cmake_install.cmake")
  include("/home/antonyhwang/infinitam_ws/build/InfiniTAM/InfiniTAM/InputSource/cmake_install.cmake")
  include("/home/antonyhwang/infinitam_ws/build/InfiniTAM/InfiniTAM/ITMLib/cmake_install.cmake")
  include("/home/antonyhwang/infinitam_ws/build/InfiniTAM/InfiniTAM/MiniSlamGraphLib/cmake_install.cmake")
  include("/home/antonyhwang/infinitam_ws/build/InfiniTAM/InfiniTAM/ORUtils/cmake_install.cmake")

endif()

