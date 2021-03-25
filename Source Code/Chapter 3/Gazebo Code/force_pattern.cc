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
#include <fstream>
#include <math.h>
#define PI 3.14159265

namespace gazebo
{
  class ForcePattern : public ModelPlugin
  {
  
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store a pointer to the model
      this->model = _parent;

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&ForcePattern::OnUpdate, this));

      AddForceObservationLabels();
    }

    // Called by the world update start event
    public: void OnUpdate()
    {
        const physics::WorldPtr& worldPtr = model->GetWorld();
		common::Time simulationTime = worldPtr->SimTime();
		double simTime = simulationTime.Double();

        if(isTimeBased)
        {
            ComputeForceVector(currentForcePattern, simTime);
        }
        else
        {
            ComputeTickBasedForceVector(currentForcePattern);
            crtIteration ++;
        }

        this->model->GetLink("base_link")->AddForce(appliedForceVector);
        AddForceObservation(simTime);

        if (simTime >= totalExperimentDuration)
        {
            outputFile.close();
        }
    }

    public: void AddForceObservationLabels()
    {
        // This function creates a .csv file and adds the first row consisting of the observations labels to that file.
        outputFile.open("appliedForce.csv");
        outputFile<<"sim_time, applied_force_x, applied_force_y, applied_force_z\n";
    }

    public: void AddForceObservation(double simTime)
    {
        // This function adds a new observation to the .csv file previously opened.
        // Note that an observation simply consists of the current simulation time and the values of the appliedForceVector. 
        outputFile << simTime << "," << appliedForceVector[0] << "," << appliedForceVector[1] << "," << appliedForceVector[2] << "\n";
    }

    private: void ComputeForceVector(int patternNumber, double currentTime)
    {
        switch(patternNumber)
        {
            case 0:
                ComputeTimeConstantForce(currentTime);
                break;
            case 1:
                ComputeForcePatternOne(currentTime);
                break;
            case 2:
                ComputeForcePatternTwo(currentTime);
                break;
            case 3:
                ComputeForcePatternThree(currentTime);
                break;
            case 4:
                ComputeForcePatternFour(currentTime);
                break;
            default:
                appliedForceVector = ignition::math::Vector3d(0, 0, 0);
                break;
        }
    }

    private: void ComputeTickBasedForceVector(int patternNumber)
    {
        // This function computes and returns the force vector that should be applied every iteration according to any of the 4 existing patterns.

        switch (patternNumber)
        {
            case 0:
                ComputeTickConstantForce();
                break;
            case 1:
                ComputeTickPatternOne();
                break;
            case 2:
                ComputeTickPatternTwo();
                break;
            case 3:
                ComputeTickPatternThree();
                break;
            case 4:
                ComputeTickPatternFour();
                break;
            default:
                appliedForceVector = ignition::math::Vector3d(0, 0, 0);
                break;
        }
    }

    private: void ComputeTimeConstantForce(double currentPatternTime)
    {
        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (currentPatternTime <= patternDuration)
        {
            appliedForceVector = ignition::math::Vector3d(0, constantForceValue, 0);
        }
    } 
    
    private: void ComputeForcePatternOne(double currentPatternTime)
    {
        // This function computes and returns the force vector that should be applied at every timestamp according to Pattern 1.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);
        if (currentPatternTime <= patternDuration)
        {
            float yForce = 0.0f;
            
            if (currentPatternTime <= 2.0f)
            {
                yForce = 5 * currentPatternTime;
            }
            else if (currentPatternTime <= 3.0f)
            {
                yForce = 10;
            }
            else if (currentPatternTime <= 5.0f)
            {
                yForce = 10 - 5 * (currentPatternTime - 3.0f);
            }

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    } 

    private: void ComputeForcePatternTwo(double currentPatternTime)
    {   
        // This function computes and returns the force vector that should be applied at every timestamp according to Pattern 2.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (currentPatternTime <= patternDuration) 
        {
            float yForce = 0.0f;

            if (currentPatternTime < 0.1f)
            {
                yForce = 100 * currentPatternTime;
            }
            else if (currentPatternTime < 4.9f)
            {
                yForce = 10;
            }
            else if (currentPatternTime <= 5.0f)
            {
                yForce = 10 - 100 * (currentPatternTime - 4.9f);
            }

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    private: void ComputeForcePatternThree(double currentPatternTime) 
    {
        // This function computes and returns the force vector that should be applied at every timestamp according to Pattern 3.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (currentPatternTime <= patternDuration)
        {
            float yForce = 0.0f;

            // Note that Pattern 3 consists of applying the same sub-pattern 3 times. 
            // Therefore, it can be computed more easily by 'shifting' the currentPatternTime and only providing the rules for the first time the sub-pattern is executed.
            if (currentPatternTime >= 0.5f && currentPatternTime < 1.0f)
            {
                // Second repetition of the same sub-pattern.
                currentPatternTime -= 0.5f;
            }
            else if (currentPatternTime >= 1.0f && currentPatternTime < 1.5f)
            {
                // Third repetition of the same sub-pattern.
                currentPatternTime -= 1.0f;
            }

            // Rules for the execution of the sub-pattern.
            if (currentPatternTime < 0.1f) 
            {
                yForce = 200 * currentPatternTime + 0.2;
            }
            else if (currentPatternTime < 0.4f) 
            {
                yForce = 20;
            }
            else if (currentPatternTime < 0.5f) 
            {
                yForce = 20 - 200 * (currentPatternTime - 0.4f);
            }

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    private: void ComputeForcePatternFour(double currentPatternTime)
    {
        // This function computes and returns the force vector that should be applied at every timestamp according to Pattern 4.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (currentPatternTime <= patternDuration)
        {
            float yForce = 20 * abs(sin(PI * currentPatternTime));
            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    private: void ComputeTickConstantForce()
    {
        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (crtIteration < totalIterations)
        {
            appliedForceVector = ignition::math::Vector3d(0, constantForceValue, 0);
        }
    }

    private: void ComputeTickPatternOne()
    {
        // This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 1.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (crtIteration < totalIterations)
        {
            float yForce = 0.0f;

            if (crtIteration <= 2000)
            {
                yForce = 0.005 * crtIteration;
            }
            else if (crtIteration <= 3000)
            {
                yForce = 10;
            }
            else if (crtIteration <= 5000)
            {
                yForce = 10 - 0.005 * (crtIteration - 3000);
            }

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    private: void ComputeTickPatternTwo() 
    {
        // This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 2.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (crtIteration < totalIterations)
        {
            float yForce = 0.0f;

            if (crtIteration < 100)
            {
                yForce = crtIteration * 1.0f / 10;
            }
            else if (crtIteration < 4900)
            {
                yForce = 10;
            }
            else if (crtIteration < 5000)
            {
                yForce = 10 - (crtIteration - 4900) * 1.0f / 10;
            }

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    private: void ComputeTickPatternThree()
    {
        // This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 3.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (crtIteration < totalIterations)
        {
            float yForce = 0.0f;

            // Note that the observation made below, together with the fact that crtIteration is a variable of the class leads to the need of an auxiliary variable.
            int auxiliary = crtIteration;

            // Note that Pattern 3 consists of applying the same sub-pattern 3 times. 
            // Therefore, it can be computed more easily by 'shifting' the crtIteration and only providing the rules for the first time the sub-pattern is executed.
            if (auxiliary >= 500 && auxiliary < 1000)
            {
                // Second repetition of the same sub-pattern.
                auxiliary -= 500;
            }
            else if (auxiliary >= 1000 && auxiliary < 1500)
            {
                // Third repetition of the same sub-pattern.
                auxiliary -= 1000;
            }

            // Rules for the execution of the sub-pattern.
            if (auxiliary < 100)
            {
                yForce = 0.2 * auxiliary;
            }
            else if (auxiliary < 400)
            {
                yForce = 20;
            }
            else if (auxiliary < 500)
            {
                yForce = 20 - 0.2 * (auxiliary - 400);
            }

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    private: void ComputeTickPatternFour()
    {
        // This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 4.

        appliedForceVector = ignition::math::Vector3d(0, 0, 0);

        if (crtIteration < totalIterations)
        {
            float yForce = 20 * abs(sin((crtIteration * PI / 1000)));

            appliedForceVector = ignition::math::Vector3d(0, yForce, 0);
        }
    }

    // Pointer to the model.
    private: physics::ModelPtr model;

    // Pointer to the update event connection.
    private: event::ConnectionPtr updateConnection;

    // Variable holding the force pattern in use.
    private: int currentForcePattern = 0;

    // Variable holding the number of iterations executed since the experiment began.
    private: int crtIteration = 0;

    // Variable holding the total number of iterations of the CurrentForcePattern, deciding how many ticks a force is going to be applied to the Cube.
    private: int totalIterations = 5000;

    // Variable holding the duration of the currentForcePattern, deciding how long a force is going to be applied to the Cube.
    private: double patternDuration = 5.0f;

    // Variable holding the experiment duration, therefore deciding the time period for which Observations will be taken.
    private: double totalExperimentDuration = 7.0f;

    // Variable storing the vector representing the force that will be applied to the Cube.
    private: ignition::math::Vector3d appliedForceVector = ignition::math::Vector3d(0, 0, 0);

    // Stream representing the output file in which Observations are written.
    private: std::ofstream outputFile;

    // Auxiliary boolean deciding if the experiment is time or tick based.
    private: bool isTimeBased = false;

    // Variable holding the value of the constant force that will be applied.
    private: float constantForceValue = 0;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(ForcePattern)
}