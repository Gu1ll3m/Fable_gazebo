#include "joint_controller/joint_controller.h"
#include <pluginlib/class_list_macros.h>
#include <stdio.h>

namespace gazebo{

///Controller initialitzation in non-realtime
bool joint_controller::init(pr2_mechanism_model::RobotState *robot, ros::NodeHandle &n)
{
   fprintf(stderr, "Joint Controller::init   check point 1\n");
   
    std::string joint_name;
    if (!n.getParam("joint_name", joint_name))
    {
       ROS_ERROR("No joint given in namespace: '%s')", n.getNamespace().c_str());
       return false;
    }

    joint_state_ = robot->getJointState(joint_name);
    if(!joint_state_)
    {
      ROS_ERROR("Joint Controller cound not find joint named '%s'", joint_name.c_str());
      return false;
    }
    fprintf(stderr, joint_name.c_str());
    fprintf(stderr, "initial pose = ");
   return true;
}

/// Controller startup in realtime
void joint_controller::starting()
{
   init_pos_ = joint_state_->position_;
   fprintf(stderr, "value %f",init_pos_);
}


/// Controller update loop in realtime   (gets called at 1000Hz)
void joint_controller::update()
{
   //fprintf(stderr, "Update executed\n");
	//lower="-1.57" upper="1.57"
   double desired_pos = init_pos_ + 2 * sin(ros::Time::now().toSec());
   double current_pos = joint_state_->position_;
   joint_state_->commanded_effort_ = -2 * (current_pos - desired_pos);
}

///Controller stopping in realtime
void joint_controller::stopping()
{}

} //namespace

/// Register controller to pluginlib
PLUGINLIB_DECLARE_CLASS(joint_controller,JointControllerPlugin, 
                        gazebo::joint_controller, 
                        pr2_controller_interface::Controller)

