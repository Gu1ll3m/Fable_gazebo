#!/bin/bash

rosrun xacro xacro.py 2DOF_fable_final.xacro > 2DOF_gazebo.urdf

roslaunch fable fable_gazebo.launch


