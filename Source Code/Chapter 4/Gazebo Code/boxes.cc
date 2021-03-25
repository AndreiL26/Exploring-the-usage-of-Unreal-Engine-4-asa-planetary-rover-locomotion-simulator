/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#include <string>

#include <ignition/math/Pose3.hh>
#include <ignition/math/Quaternion.hh>
#include <ignition/math/Vector3.hh>

#include "gazebo/msgs/msgs.hh"
#include "gazebo/physics/physics.hh"
#include "boxes.hh"

/* A. Lazar change begin */
#include <ignition/math/Angle.hh>
#include <fstream>
/* A. Lazar change end */


using namespace gazebo;
using namespace benchmark;

/////////////////////////////////////////////////
// Boxes:
// Spawn a single box and record accuracy for momentum and energy
// conservation
void BoxesTest::Boxes(const std::string &_physicsEngine
                    , double _dt
                    , int _modelCount
                    , bool _collision
                    , bool _complex)
{
  // Load a blank world (no ground plane)
  Load("worlds/blank.world", true, _physicsEngine);
  physics::WorldPtr world = physics::get_world("default");
  ASSERT_NE(world, nullptr);

  // Verify physics engine type
  physics::PhysicsEnginePtr physics = world->Physics();
  ASSERT_NE(physics, nullptr);
  ASSERT_EQ(physics->GetType(), _physicsEngine);

  // get gravity value
  if (!_complex)
  {
    world->SetGravity(ignition::math::Vector3d::Zero);
  }
  ignition::math::Vector3d g = world->Gravity();

  // Box size
  const double dx = 0.1;
  const double dy = 0.4;
  const double dz = 0.9;
  const double mass = 10.0;
  // expected inertia matrix, recompute if the above change
  const double Ixx = 0.80833333;
  const double Iyy = 0.68333333;
  const double Izz = 0.14166667;
  const ignition::math::Matrix3d I0(Ixx, 0.0, 0.0
                                  , 0.0, Iyy, 0.0
                                  , 0.0, 0.0, Izz);

  // Create box with inertia based on box of uniform density
  msgs::Model msgModel;
  msgs::AddBoxLink(msgModel, mass, ignition::math::Vector3d(dx, dy, dz));
  if (!_collision)
  {
    // Test without collision shapes.
    msgModel.mutable_link(0)->clear_collision();
  }

  // spawn multiple boxes
  // compute error statistics only on the last box
  ASSERT_GT(_modelCount, 0);
  physics::ModelPtr model;
  physics::LinkPtr link;

  // initial linear velocity in global frame
  ignition::math::Vector3d v0;

  // initial angular velocity in global frame
  ignition::math::Vector3d w0;

  // initial energy value
  double E0;

  if (!_complex)
  {
    v0.Set(-0.9, 0.4, 0.1);
    // Use angular velocity with one non-zero component
    // to ensure linear angular trajectory
    w0.Set(0.5, 0, 0);
    E0 = 5.001041625;
  }
  else
  {
    v0.Set(-2.0, 2.0, 8.0);
    // Since Ixx > Iyy > Izz,
    // angular velocity with large y component
    // will cause gyroscopic tumbling
    w0.Set(0.1, 5.0, 0.1);
    E0 = 368.54641249999997;
  }

  for (int i = 0; i < _modelCount; ++i)
  {
    // give models unique names
    msgModel.set_name(this->GetUniqueString("model"));
    // give models unique positions
    msgs::Set(msgModel.mutable_pose()->mutable_position(),
              ignition::math::Vector3d(0.0, dz*2*i, 0.0));

    model = this->SpawnModel(msgModel);
    ASSERT_NE(model, nullptr);

    link = model->GetLink();
    ASSERT_NE(link, nullptr);

    // Set initial conditions
    link->SetLinearVel(v0);
    link->SetAngularVel(w0);
  }
  ASSERT_EQ(v0, link->WorldCoGLinearVel());
  ASSERT_EQ(w0, link->WorldAngularVel());
  ASSERT_EQ(I0, link->GetInertial()->MOI());
  ASSERT_NEAR(link->GetWorldEnergy(), E0, 1e-6);

  // initial time
  common::Time t0 = world->SimTime();

  // initial linear position in global frame
  ignition::math::Vector3d p0 = link->WorldInertialPose().Pos();

  // initial angular momentum in global frame
  ignition::math::Vector3d H0 = link->WorldAngularMomentum();
  ASSERT_EQ(H0, ignition::math::Vector3d(Ixx, Iyy, Izz) * w0);
  double H0mag = H0.Length();

  // change step size after setting initial conditions
  // since simbody requires a time step
  physics->SetMaxStepSize(_dt);
  const double simDuration = 10.0;
  int steps = ceil(simDuration / _dt);

  // variables to compute statistics on
  ignition::math::Vector3Stats linearPositionError;
  ignition::math::Vector3Stats linearVelocityError;
  ignition::math::Vector3Stats angularPositionError;
  ignition::math::Vector3Stats angularMomentumError;
  ignition::math::SignalStats energyError;
  {
    const std::string statNames = "maxAbs";
    EXPECT_TRUE(linearPositionError.InsertStatistics(statNames));
    EXPECT_TRUE(linearVelocityError.InsertStatistics(statNames));
    EXPECT_TRUE(angularPositionError.InsertStatistics(statNames));
    EXPECT_TRUE(angularMomentumError.InsertStatistics(statNames));
    EXPECT_TRUE(energyError.InsertStatistics(statNames));
  }


  /* A. Lazar change begin */
  // Add labels to log additional experiment data
  std::ofstream outputFile;
  std::string filename;
  char aux[10];
  snprintf(aux, 9, "%f", _dt);
  if(!_complex)
  {
     filename.assign("test_data/simple_test_");
  }
  else
  {
     filename.assign("test_data/complex_test_");
  }

  filename = filename + _physicsEngine;
  filename.append("_");
  filename.append(aux);
  filename.append(".csv"); 
  outputFile.open(filename.c_str());
  outputFile<<"Time"<<","<<"IsComplex"<<","<<"X Velocity"<<","<<"Y Velocity"<<","<<"Z Velocity"<<","<<"X Velocity Error"<<","<<"Y Velocity Error"<<","<<"Z Velocity Error"<<",";
  outputFile<<"X Position"<<","<<"Y Position"<<","<<"Z Position"<<","<<"X Position Error"<<","<<"Y Position Error"<<","<<"Z Position Error"<<",";
  outputFile<<"X Angular Momentum"<<","<<"Y Angular Momentum "<<","<<"Z Angular Momentum"<<","<<"X Angular Momentum Error"<<","<<"Y Angular Momentum Error"<<","<<"Z Angular Momentum Error"<<",";
  outputFile<<"X Angular Velocity"<<","<<"Y Angular Velocity"<<","<<"Z Angular Velocity"<<",";
  outputFile<<"Energy"<<","<<"Energy Error"<<",";
  outputFile<<"Roll"<<","<<"Yaw"<<","<<"Pitch";
  outputFile<<"\n";
  /* A. Lazar change end */

  // unthrottle update rate
  physics->SetRealTimeUpdateRate(0.0);
  common::Time startTime = common::Time::GetWallTime();
  for (int i = 0; i < steps; ++i)
  {
    world->Step(1);

    // current time
    double t = (world->SimTime() - t0).Double();

    // linear velocity error
    ignition::math::Vector3d v = link->WorldCoGLinearVel();
    ignition::math::Vector3d vel_aux = v - (v0 + g*t);
    linearVelocityError.InsertData(v - (v0 + g*t));

    // linear position error
    ignition::math::Vector3d p = link->WorldInertialPose().Pos();
    ignition::math::Vector3d p_aux = p - (p0 + v0 * t + 0.5*g*t*t);
    linearPositionError.InsertData(p - (p0 + v0 * t + 0.5*g*t*t));


    // angular momentum error
    ignition::math::Vector3d H = link->WorldAngularMomentum();
    ignition::math::Vector3d H_aux = (H - H0) / H0mag;
    angularMomentumError.InsertData((H - H0) / H0mag);

    // energy error
    energyError.InsertData((link->GetWorldEnergy() - E0) / E0);

    /* A. Lazar change begin */
    // Add the actual data 
    outputFile << t <<",";
    if (!_complex) 
    {
      outputFile << "0" << ",";
    }
    else
    {
      outputFile << "1" << ",";
    }

    ignition::math::Vector3d angularVel = link->WorldAngularVel();
    ignition::math::Quaternion<double> a = link->WorldInertialPose().Rot();

    outputFile << v[0] << "," << v[1] << "," << v[2] << "," << vel_aux[0] << "," << vel_aux[1] << "," << vel_aux[2]<<",";
    outputFile << p[0] << "," << p[1] << "," << p[2] << "," << p_aux[0] << "," << p_aux[1] << "," << p_aux[2]<<",";
    outputFile << H[0] << "," << H[1] << "," << H[2] << "," << H_aux[0] << "," << H_aux[1] << "," << H_aux[2]<<",";
    outputFile << angularVel[0] << "," << angularVel[1] << "," << angularVel[2] << ",";
    outputFile << link->GetWorldEnergy() << "," << (link->GetWorldEnergy() - E0) / E0<<",";
    ignition::math::Angle Roll = ignition::math::Angle(a.Roll());
    ignition::math::Angle Yaw = ignition::math::Angle(a.Yaw());
    ignition::math::Angle Pitch = ignition::math::Angle(a.Pitch());
    outputFile << Roll.Degree()<< "," << Yaw.Degree() << "," << Pitch.Degree() << ",";
      
    outputFile << '\n';
    /* A. Lazar change end */
  }

  common::Time elapsedTime = common::Time::GetWallTime() - startTime;
  this->Record("wallTime", elapsedTime.Double());
  common::Time simTime = (world->SimTime() - t0).Double();
  ASSERT_NEAR(simTime.Double(), simDuration, _dt*1.1);
  this->Record("simTime", simTime.Double());
  this->Record("timeRatio", elapsedTime.Double() / simTime.Double());

  // Record statistics on pitch and yaw angles
  this->Record("energy0", E0);
  this->Record("energyError_", energyError);
  this->Record("angMomentum0", H0mag);
  this->Record("angMomentumErr_", angularMomentumError.Mag());
  this->Record("angPositionErr", angularPositionError);
  this->Record("linPositionErr_", linearPositionError.Mag());
  this->Record("linVelocityErr_", linearVelocityError.Mag());

  /* A. Lazar change begin */
  outputFile.close();
  /* A. Lazar change end */
}

/////////////////////////////////////////////////
TEST_P(BoxesTest, Boxes)
{
  std::string physicsEngine = std::tr1::get<0>(GetParam());
  double dt                 = std::tr1::get<1>(GetParam());
  int modelCount            = std::tr1::get<2>(GetParam());
  bool collision            = std::tr1::get<3>(GetParam());
  bool isComplex            = std::tr1::get<4>(GetParam());
  gzdbg << physicsEngine
        << ", dt: " << dt
        << ", modelCount: " << modelCount
        << ", collision: " << collision
        << ", isComplex: " << isComplex
        << std::endl;
  RecordProperty("engine", physicsEngine);
  this->Record("dt", dt);
  RecordProperty("modelCount", modelCount);
  RecordProperty("collision", collision);
  RecordProperty("isComplex", isComplex);
  Boxes(physicsEngine
      , dt
      , modelCount
      , collision
      , isComplex);


}
