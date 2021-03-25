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

#include "ExperimentalCubeOne.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/Material.h"
#include "TextFileManager.h"

AExperimentalCubeOne::AExperimentalCubeOne()
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

void AExperimentalCubeOne::BeginPlay()
{
	Super::BeginPlay();
}

void AExperimentalCubeOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Frame duration:%f"), DeltaTime);

	if (CurrentTime >= TotalExperimentDuration)
	{
		if (!bAddedLabels)
		{
			AddObservationLabels();
		}
	}
	else
	{
		AddObservation();
	}
	
	CurrentTime += DeltaTime;
}

void AExperimentalCubeOne::AddObservationLabels() 
{
	// This function adds labels to the ObservationsArray and saves the content of the beforementioned array to a .csv file.
	FString ObservationLabels = FString("Time") + "," + FString("X Velocity") + "," + FString("Y Velocity") + "," + FString("Z Velocity") + "," +
								FString("X Position") + "," + FString("Y Position") + "," + FString("Z Position") + "," + FString("Roll") + "," + FString("Yaw") + "," + FString("Pitch") + "," +
								FString("X Angular Velocity") + "," + FString("Y Angular Velocity") + "," + FString("Z Angular Velocity");

	ObservationsArray.Insert(ObservationLabels, 0);
	ATextFileManager::SaveArrayText(UKismetSystemLibrary::GetProjectDirectory(), FileName, ObservationsArray, true);

	// Modify the value of the auxiliary so that labels are added only once.
	bAddedLabels = true;
}

void AExperimentalCubeOne::AddObservation() 
{
	// This function adds an Observation to the ObservationsArray.
	// Note that an Observations consists of the current time, the linear velocity, angular velocity, position and rotation of the cube.
	FString Observation = "";
	FVector VelocityVector = CubeMesh->GetComponentVelocity();
	FVector PositionVector = GetActorLocation();
	FRotator RotationVector = GetActorRotation();
	FVector AngularVelocityVector = CubeMesh->GetPhysicsAngularVelocityInDegrees();

	Observation += FString::SanitizeFloat(CurrentTime) + ",";
	Observation += FString::SanitizeFloat(VelocityVector.X) + "," + FString::SanitizeFloat(VelocityVector.Y) + "," + FString::SanitizeFloat(VelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(PositionVector.X + DisplacementVector.X) + "," + FString::SanitizeFloat(PositionVector.Y + DisplacementVector.Y) + "," + FString::SanitizeFloat(PositionVector.Z + DisplacementVector.Z) + ",";
	Observation += FString::SanitizeFloat(RotationVector.Roll) + "," + FString::SanitizeFloat(RotationVector.Yaw) + "," + FString::SanitizeFloat(RotationVector.Pitch) + ",";
	Observation += FString::SanitizeFloat(AngularVelocityVector.X) += "," + FString::SanitizeFloat(AngularVelocityVector.Y) + "," + FString::SanitizeFloat(AngularVelocityVector.Z);

	ObservationsArray.Add(Observation);
}