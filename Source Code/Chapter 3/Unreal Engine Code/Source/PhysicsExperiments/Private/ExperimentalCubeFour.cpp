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

#include "ExperimentalCubeFour.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TextFileManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMesh.h"
#include <math.h>

AExperimentalCubeFour::AExperimentalCubeFour() 
{
	// Create and attach a Static Mesh to the Cube.
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube mesh"));
	CubeMesh->SetupAttachment(RootComponent);
	CubeMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Physics_Experiments/Shapes/Shape_Cube.Shape_Cube")).Object);

	// Initialize basic Physics properties for the Mesh.
	CubeMesh->SetSimulatePhysics(true);
	CubeMesh->SetMassOverrideInKg();

	PrimaryActorTick.bCanEverTick = true;

	// Bind the delegate used for Physics Sub-Stepping.
	OnCalculateCustomPhysics.BindUObject(this, &AExperimentalCubeFour::CustomPhysics);
}

void AExperimentalCubeFour::BeginPlay() 
{
	Super::BeginPlay();
	DisplacementVector = GetActorLocation();
}

void AExperimentalCubeFour::AddObservationLabels() 
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

void AExperimentalCubeFour::AddObservation() 
{
	// This function adds an Observation to the ObservationsArray.
	// Note that an Observations consists of the current time, the linear velocity, angular velocity, position and rotation of the cube and the force applied to the cube.
	FString Observation = "";
	FVector VelocityVector = CubeMesh->GetComponentVelocity();
	FVector PositionVector = GetActorLocation();
	FRotator RotationVector = GetActorRotation();
	FVector AngularVelocityVector = CubeMesh->GetPhysicsAngularVelocityInDegrees();

	// Note that there is a 0.5 seconds delay to account for any initialization that UE4 might perform and that might lead to unexpected behaviour.
	Observation += FString::SanitizeFloat(CrtTime - 0.5f) + ",";
	Observation += FString::SanitizeFloat(VelocityVector.X) + "," + FString::SanitizeFloat(VelocityVector.Y) + "," + FString::SanitizeFloat(VelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(PositionVector.X - DisplacementVector.X) + "," + FString::SanitizeFloat(PositionVector.Y - DisplacementVector.Y) + "," + FString::SanitizeFloat(PositionVector.Z - DisplacementVector.Z) + ",";
	Observation += FString::SanitizeFloat(RotationVector.Roll) + "," + FString::SanitizeFloat(RotationVector.Yaw) + "," + FString::SanitizeFloat(RotationVector.Pitch) + ",";
	Observation += FString::SanitizeFloat(AngularVelocityVector.X) += "," + FString::SanitizeFloat(AngularVelocityVector.Y) + "," + FString::SanitizeFloat(AngularVelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(ForceVector.X) += "," + FString::SanitizeFloat(ForceVector.Y) + "," + FString::SanitizeFloat(ForceVector.Z);

	ObservationsArray.Add(Observation);
}

FVector ComputeTickPatternOne(int CurrentIteration, int TotalIterations) 
{
	// This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 1.
	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentIteration < TotalIterations)
	{
		float yForce = 0.0f;

		if (CurrentIteration <= 2000)
		{
			yForce = 0.005 * CurrentIteration;
		}
		else if (CurrentIteration <= 3000)
		{
			yForce = 10;
		}
		else if (CurrentIteration <= 5000)
		{
			yForce = 10 - 0.005 * (CurrentIteration - 3000);
		}

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeTickPatternTwo(int CurrentIteration, int TotalIterations) 
{
	// This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 2.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentIteration < TotalIterations)
	{
		float yForce = 0.0f;

		if (CurrentIteration < 100)
		{
			yForce = CurrentIteration * 1.0f / 10;
		}
		else if (CurrentIteration < 4900)
		{
			yForce = 10;
		}
		else if (CurrentIteration < 5000)
		{
			yForce = 10 - (CurrentIteration - 4900) * 1.0f / 10;
		}

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeTickPatternThree(int CurrentIteration, int TotalIterations) 	
{
	// This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 3.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentIteration < TotalIterations)
	{
		float yForce = 0.0f;

		// Note that Pattern 3 consists of applying the same sub-pattern 3 times. 
		// Therefore, it can be computed more easily by 'shifting' the CurrentIteration and only providing the rules for the first time the sub-pattern is executed.
		if (CurrentIteration >= 500 && CurrentIteration < 1000)
		{
			// Second repetition of the same sub-pattern.
			CurrentIteration -= 500;
		}
		else if (CurrentIteration >= 1000 && CurrentIteration < 1500)
		{
			// Third repetition of the same sub-pattern.
			CurrentIteration -= 1000;
		}

		// Rules for the execution of the sub-pattern.
		if (CurrentIteration < 100)
		{
			yForce = 0.2 * CurrentIteration;
		}
		else if (CurrentIteration < 400)
		{
			yForce = 20;
		}
		else if (CurrentIteration < 500)
		{
			yForce = 20 - 0.2 * (CurrentIteration - 400);
		}

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeTickPatternFour(int CurrentIteration, int TotalIterations) 	
{
	// This function computes and returns the force vector that should be applied every iteration of the physics engine according to Pattern 4.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentIteration < TotalIterations)
	{
		float yForce = 20 * abs(sin((CurrentIteration * PI / 1000)));

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeTickConstantForce(int CurrentIteration, int TotalPatternIterations, float ConstantForce)
{
	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentIteration < TotalPatternIterations)
	{
		AppliedForceVector =  FVector(0, ConstantForce, 0);
	}

	return AppliedForceVector;
}

FVector AExperimentalCubeFour::ComputeTickBasedForce(int PatternNumber, int CurrentIteration)
{
	// This function computes and returns the force vector that should be applied every iteration according to any of the 4 existing patterns.
	switch (PatternNumber)
	{
		case 0:
			return ComputeTickConstantForce(CurrentIteration, TotalPatternIterations, ConstantForce);
		case 1:
			return ComputeTickPatternOne(CurrentIteration, TotalPatternIterations);
		case 2:
			return ComputeTickPatternTwo(CurrentIteration, TotalPatternIterations);
		case 3:
			return ComputeTickPatternThree(CurrentIteration, TotalPatternIterations);
		case 4:
			return ComputeTickPatternFour(CurrentIteration, TotalPatternIterations);
		default:
			return FVector(0, 0, 0);
	}
}

void AExperimentalCubeFour::PhysicsTick_Implementation(float SubstepDeltaTime) 
{
	// This functions applies the force vector to the cube.
	ForceVector = ComputeTickBasedForce(CurrentForcePattern, CrtIteration);
	CubeMesh->AddImpulseAtLocation(ForceVector * SubstepDeltaTime, CubeMesh->GetCenterOfMass() + ForceVectorOffset);
	CrtIteration++;
}

void AExperimentalCubeFour::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance)
{
	// Note that there is a 0.5 seconds delay to account for any initialization that UE4 performs and that might lead to unexpected behaviour.
	if (CrtTime > 0.5f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Frame duration:%f\n"), DeltaTime);
		PhysicsTick(DeltaTime);
		AddObservation();
	}
	CrtTime += DeltaTime;
}

FVector ComputeForcePatternOne(float CurrentPatternTime, float PatternDuration)
{
	// This function computes and returns the force vector that should be applied at every timestamp according to Pattern 1.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentPatternTime <= PatternDuration)
	{
		float yForce = 0.0f;
		
		if (CurrentPatternTime <= 2.0f)
		{
			yForce = 5 * CurrentPatternTime;
		}
		else if (CurrentPatternTime <= 3.0f)
		{
			yForce = 10;
		}
		else if (CurrentPatternTime <= 5.0f)
		{
			yForce = 10 - 5 * (CurrentPatternTime - 3.0f);
		}

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeForcePatternTwo(float CurrentPatternTime, float PatternDuration)
{	
	// This function computes and returns the force vector that should be applied at every timestamp according to Pattern 2.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentPatternTime <= PatternDuration) 
	{
		float yForce = 0.0f;

		if (CurrentPatternTime < 0.1f)
		{
			yForce = 100 * CurrentPatternTime;
		}
		else if (CurrentPatternTime < 4.9f)
		{
			yForce = 10;
		}
		else if (CurrentPatternTime <= 5.0f)
		{
			yForce = 10 - 100 * (CurrentPatternTime - 4.9f);
		}

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeForcePatternThree(float CurrentPatternTime, float PatternDuration) 
{
	// This function computes and returns the force vector that should be applied at every timestamp according to Pattern 3.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentPatternTime <= PatternDuration)
	{
		float yForce = 0.0f;

		// Note that Pattern 3 consists of applying the same sub-pattern 3 times. 
		// Therefore, it can be computed more easily by 'shifting' the CurrentPatternTime and only providing the rules for the first time the sub-pattern is executed.
		if (CurrentPatternTime >= 0.5f && CurrentPatternTime < 1.0f)
		{
			// Second repetition of the same sub-pattern.
			CurrentPatternTime -= 0.5f;
		}
		else if (CurrentPatternTime >= 1.0f && CurrentPatternTime < 1.5f)
		{
			// Third repetition of the same sub-pattern.
			CurrentPatternTime -= 1.0f;
		}

		// Rules for the execution of the sub-pattern.
		if (CurrentPatternTime < 0.1f) 
		{
			yForce = 200 * CurrentPatternTime + 0.2;
		}
		else if (CurrentPatternTime < 0.4f) 
		{
			yForce = 20;
		}
		else if (CurrentPatternTime < 0.5f) 
		{
			yForce = 20 - 200 * (CurrentPatternTime - 0.4f);
		}

		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeForcePatternFour(float CurrentPatternTime, float PatternDuration)
{
	// This function computes and returns the force vector that should be applied at every timestamp according to Pattern 4.

	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentPatternTime <= PatternDuration)
	{
		float yForce = 20 * abs(sin(PI * CurrentPatternTime));
		AppliedForceVector = FVector(0, yForce, 0);
	}

	return AppliedForceVector;
}

FVector ComputeTimeConstantForce(float CurrentTime, float PatternDuration, float ConstantForce)
{
	FVector AppliedForceVector = FVector(0, 0, 0);

	if (CurrentTime < PatternDuration)
	{
		AppliedForceVector =  FVector(0, ConstantForce, 0);
	}

	return AppliedForceVector;
}

FVector AExperimentalCubeFour::ComputeForceVector(int PatternNumber, float CurrentTime)
{
	// This function computes and returns the force vector that should be applied every timestamp according to any of the 4 existing patterns.

	switch (PatternNumber) 
	{
		case 0:
			return ComputeTimeConstantForce(CurrentTime, PatternDuration, ConstantForce);
		case 1:
			return ComputeForcePatternOne(CurrentTime, PatternDuration);
		case 2:
			return ComputeForcePatternTwo(CurrentTime, PatternDuration);
		case 3:
			return ComputeForcePatternThree(CurrentTime, PatternDuration);
		case 4:
			return ComputeForcePatternFour(CurrentTime, PatternDuration);
		default:
			return FVector(0, 0, 0);
	}
}

void AExperimentalCubeFour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Frame duration:%f"), DeltaTime);
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
		if (bIsTimeBased)
		{
			CrtTime += DeltaTime;
			if (CrtTime > 0.5f)
			{
				AddObservation();

				// Note that the CrtTime - 0.5 seconds is passed as argument because of the 0.5 seconds delay mentioned throughout the code.
				ForceVector = ComputeForceVector(CurrentForcePattern, CrtTime - 0.5f);
				CubeMesh->AddForceAtLocation(ForceVector, CubeMesh->GetCenterOfMass() + ForceVectorOffset);
			}
		}
		else
		{
				CubeMesh->GetBodyInstance()->AddCustomPhysics(OnCalculateCustomPhysics);
		}
	}
}
