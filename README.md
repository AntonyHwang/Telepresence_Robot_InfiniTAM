# Telepresence Robot InfiniTAM

This is the main branch of the software bundle "InfiniTAM", the current version is actively maintained by:

  Antony Hwang <antony.hwang.14@ucl.ac.uk>  

For more information about InfiniTAM please visit the project website <http://www.infinitam.org>. 

# 1. Building the System

### 1.1 Requirements

Hardware

  - Robot
    Intel RealSense D435 Camera (IMU case CAD File at Telepresence_Robot_InfiniTAM/cad_files/)
    SparkFun 9DoF Razor IMU M0 - SEN-14001
    Linux 16.04
  
  - GPU Enabled PC

Several 3rd party libraries are needed for compiling InfiniTAM. The given version numbers are checked and working, but different versions might be fine as well. Some of the libraries are optional, and skipping them will reduce functionality.

  - cmake (e.g. version 2.8.10.2 or 3.2.3)
    REQUIRED for Linux, unless you write your own build system
    OPTIONAL for MS Windows, if you use MSVC instead
    available at http://www.cmake.org/

  - OpenGL / GLUT (e.g. freeglut 2.8.0 or 3.0.0)
    REQUIRED for the visualisation
    the library should run without
    available at http://freeglut.sourceforge.net/
    
  - ROS (e.g. Kinetic)
    REQUIRED
    available at http://wiki.ros.org/kinetic/Installation/Ubuntu

  - CUDA (e.g. version 6.0 or 7.0)
    OPTIONAL but REQUIRED for all GPU accelerated code
    at least with cmake it is still possible to compile the CPU part without
    available at https://developer.nvidia.com/cuda-downloads

  - librealsense2 (e.g. Intel® RealSense™ SDK 2.X)
    OPTIONAL, allows to get live images from Intel Realsense cameras
    available at https://github.com/IntelRealSense/librealsense
    
### 1.2 Sensor Calibration

Follow the calibration guide for the Razor IMU at http://wiki.ros.org/razor_imu_9dof
  - Update the AHRS firmware of the IMU with the calibration values located at Telepresence_Robot_InfiniTAM/src/razor_imu_9dof/src/Razor_AHRS/Razor_AHRS.ino
  - Update the config file located at Telepresence_Robot_InfiniTAM/src/razor_imu_9dof/config/my_razor.yaml
  - Update calibration file located at Telepresence_Robot_InfiniTAM/calib_files/calib.txt
    camera calibration paramters are published by the camera node
    
###1.3 ROS Network Setup

  To setup the ROS connections, use the following command lines:
  - Robot (NUC):
```  
    export ROS_MASTER_URI=http://Client_IP:11311
    export ROS_IP=Robot_IP
```
  - Client:
```
    export ROS_MASTER_URI=http://localhost:11311
    export ROS_IP=Client_IP
```


###1.4 Build Process

  To compile the system on the robot, use the standard catkin approach:
```
  $ catkin_make
  $ source devel/setup.bash
  $ roslaunch realsense2_camera rs_aligned_depth.launch
  $ roslaunch razor_imu_9dof razor-pub.launch
```

  To compile the system on the GPU enabled PC, use the standard catkin approach:
```
  $ catkin_make
  $ source devel/setup.bash
  $ rosrun infinitam InfiniTAM /path/to/CameraCalibrationFile/
```
