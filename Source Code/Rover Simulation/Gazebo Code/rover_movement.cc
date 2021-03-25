/*
    Copyright [2021] [Andrei Lazar]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>

namespace gazebo
{
  class RoverMovement : public ModelPlugin
  {
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store the pointer to the model
      this->model = _parent;

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&RoverMovement::OnUpdate, this));
    }

    // Called by the world update start event
    public: void OnUpdate()
    {

        this->model->GetLink("chassis")->SetForce(ignition::math::Vector3d(10,0,0));
        /*
        this->model->GetJoint("left_front_wheel_hinge")->SetForce(0,1.0);
        this->model->GetJoint("right_front_wheel_hinge")->SetForce(0,1.0);
        this->model->GetJoint("left_back_wheel_hinge")->SetForce(0,1.0);
        this->model->GetJoint("right_back_wheel_hinge")->SetForce(0,1.0);
        */
    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(RoverMovement)
}