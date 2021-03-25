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

#include "ExperimentalCubeTwo.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TextFileManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMesh.h"

AExperimentalCubeTwo::AExperimentalCubeTwo() 
{
	// Create and attach a Static Mesh to the Cube.
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube mesh"));
	CubeMesh->SetupAttachment(RootComponent);
	CubeMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Physics_Experiments/Shapes/Shape_Cube.Shape_Cube")).Object);

	// Initialize basic Physics properties for the Mesh.
	CubeMesh->SetSimulatePhysics(true);
	CubeMesh->SetMassOverrideInKg();

	PrimaryActorTick.bCanEverTick = true;
}

void AExperimentalCubeTwo::BeginPlay() 
{
	Super::BeginPlay();
	DisplacementVector = GetActorLocation();
}

void AExperimentalCubeTwo::AddObservation() 
{
	// This function adds an Observation to the ObservationsArray.
	// Note that an Observations consists of the current time, the linear velocity, angular velocity, position and rotation of the cube and the force applied to the cube.
	FString Observation = "";
	FVector VelocityVector = CubeMesh->GetComponentVelocity();
	FVector PositionVector = GetActorLocation();
	FRotator RotationVector = GetActorRotation();
	FVector AngularVelocityVector = CubeMesh->GetPhysicsAngularVelocityInDegrees();

	// Note that there is a 0.5 seconds delay to account for any initialization that UE4 performs.
	Observation += FString::SanitizeFloat(CrtTime - 0.5) + ",";
	Observation += FString::SanitizeFloat(VelocityVector.X) + "," + FString::SanitizeFloat(VelocityVector.Y) + "," + FString::SanitizeFloat(VelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(PositionVector.X - DisplacementVector.X) + "," + FString::SanitizeFloat(PositionVector.Y - DisplacementVector.Y) + "," + FString::SanitizeFloat(PositionVector.Z - DisplacementVector.Z) + ",";
	Observation += FString::SanitizeFloat(RotationVector.Roll) + "," + FString::SanitizeFloat(RotationVector.Yaw) + "," + FString::SanitizeFloat(RotationVector.Pitch) + ",";
	Observation += FString::SanitizeFloat(AngularVelocityVector.X) += "," + FString::SanitizeFloat(AngularVelocityVector.Y) + "," + FString::SanitizeFloat(AngularVelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(ForceVector.X) += "," + FString::SanitizeFloat(ForceVector.Y) + "," + FString::SanitizeFloat(ForceVector.Z);

	ObservationsArray.Add(Observation);
}

void AExperimentalCubeTwo::AddObservationLabels() 
{
	// This function adds labels to the ObservationsArray and saves the content of the beforementioned array to a .csv file.
	FString ObservationLabels = FString("Time") + "," + FString("X Velocity") + "," + FString("Y Velocity") + "," + FString("Z Velocity") + "," +
								FString("X Position") + "," + FString("Y Position") + "," + FString("Z Position") + "," + FString("Roll") + "," + FString("Yaw") + "," + FString("Pitch") + "," + 
								FString("X Angular Velocity") + "," + FString("Y Angular Velocity") + "," + FString("Z Angular Velocity") + "," + 
								FString("X Force Applied") + "," + FString("Y Force Applied") + "," + FString("Z Force Applied");

	ObservationsArray.Insert(ObservationLabels, 0);
	ATextFileManager::SaveArrayText(UKismetSystemLibrary::GetProjectDirectory(), FileName, ObservationsArray, true);

	// Modify the value of the auxiliary so that labels are added only once.
	bAddedLabels = true;
}

void AExperimentalCubeTwo::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	FVector Inertia = CubeMesh->GetInertiaTensor();
	UE_LOG(LogTemp, Warning, TEXT("Inertia:%f,%f,%f"), Inertia.X, Inertia.Y, Inertia.Z);

	// Note that there is a 0.5 seconds delay to account for any initialization that UE4 performs.
	if (CrtTime >= TotalExperimentDuration + 0.5f)
	{
		if (!bAddedLabels)
		{
			AddObservationLabels();
		}
	}
	else
	{
		if (CrtTime > 0.5f)
		{
			if (bHasAppliedForce) {
				AddObservation();
			}

			if (/*CrtTime > 1.0f &&*/ !bHasAppliedForce)
			{
				if (bIsImpulseBased)
				{
					// The constant 0.001 comes from the frame duration of Gazebo, so that the actual forces applied match in both Engines.
					CubeMesh->AddImpulseAtLocation(0.001 * ForceVector, CubeMesh->GetCenterOfMass() + ForceVectorOffset);
				}
				else
				{
					CubeMesh->AddForceAtLocation(ForceVector, CubeMesh->GetCenterOfMass() + ForceVectorOffset);
				}

				// Modify the value of the auxiliary so that the force is applied only once.
				bHasAppliedForce = true;
			}
		}
	}
	
	CrtTime += DeltaTime;
}
