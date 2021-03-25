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

#include "ExperimentalCube.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Math/Quat.h"
#include "Math/Rotator.h"
#include "TextFileManager.h"
#include "Kismet/KismetSystemLibrary.h"

AExperimentalCube::AExperimentalCube()
{
	// Create and attach a Static Mesh 
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube mesh"));
	CubeMesh->SetupAttachment(RootComponent);
	CubeMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Shapes/Shape_Cube.Shape_Cube")).Object);
	CubeMesh->SetWorldScale3D(FVector(0.1, 0.4, 0.9));

	// Initialize basic Physics properties for the Mesh.
	CubeMesh->SetSimulatePhysics(true);
	CubeMesh->SetEnableGravity(false);
	CubeMesh->SetMassOverrideInKg("Cube mesh", 10.0f, true);
	CubeMesh->SetLinearDamping(0.0f);
	CubeMesh->SetAngularDamping(0.0f);

 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	CurrentExperimentTime = 0.0f;
}

void AExperimentalCube::BeginPlay()
{
	Super::BeginPlay();

	UWorld* CrtWorld = GetWorld();
	if (CubeMesh->IsGravityEnabled())
	{
		GravityValue = FVector(0.0f, 0.0f, CrtWorld->GetGravityZ());
		FileName = "Benchmark_01_Complex_" + GetName() + ".csv";

		InitialLinearVelocity = FVector(-200.0, 200.0, 800.0);
		InitialAngularVelocity = FVector(10.0, 500.0, 10.0);
	}
	else
	{
		GravityValue = FVector(0.0f, 0.0f, 0.0f);
		FileName = "Benchmark_01_Simple_" + GetName() + ".csv";

		InitialLinearVelocity = FVector(-90, 40, 10);
		InitialAngularVelocity = FVector(50, 0, 0);
	}

	CubeMesh->SetPhysicsLinearVelocity(InitialLinearVelocity, false);
	CubeMesh->SetPhysicsAngularVelocity(InitialAngularVelocity, false);


	FVector InertiaVector = CubeMesh->GetInertiaTensor() / 10000;

	InitialAngularMomentum = (InitialAngularVelocity / 100) * InertiaVector;

	// Not necessarily needed, but leads to neater results
	CubeMesh->SetCenterOfMass(FVector(0, 0, -45));
	InitialPosition = CubeMesh->GetCenterOfMass();

	InitialEnergy = ComputeTotalEnergy();
}

float AExperimentalCube::ComputeTotalEnergy() 
{
	// Compute kinetic energy	
	float mass = CubeMesh->GetMass();
	FVector LinearVelocity = CubeMesh->GetPhysicsLinearVelocity() / 100; // convert to m/s
	FVector AngularVelocity = CubeMesh->GetPhysicsAngularVelocity() / 100; // convert to m/s
	FVector InertiaTensor = CubeMesh->GetInertiaTensor() / 10000;  // convert to kg/m^2
	float KineticEnergy = 0.5 * mass * (LinearVelocity | LinearVelocity) + 0.5 * (AngularVelocity | (InertiaTensor * AngularVelocity));

	// Compute potential energy
	FVector Position = GetActorLocation() / 100; // conver to m
	float PotentialEnergy = -mass * ((GravityValue / 100) | Position);

	return KineticEnergy + PotentialEnergy;
}

FVector AExperimentalCube::ComputeLinearVelocityError() 
{
	FVector CurrentLinearVelocity = CubeMesh->GetPhysicsLinearVelocity() / 100; // convert to m/;
	FVector ExpectedLinearVelocity = (InitialLinearVelocity / 100) + (GravityValue / 100) * CurrentExperimentTime;
	return CurrentLinearVelocity - ExpectedLinearVelocity;
}

FVector AExperimentalCube::ComputePositionError()
{
	FVector CurrentPosition = CubeMesh->GetCenterOfMass() / 100;
	FVector ExpectedPosition = InitialPosition / 100 + (InitialLinearVelocity / 100) * CurrentExperimentTime + 0.5 * (GravityValue / 100) * CurrentExperimentTime * CurrentExperimentTime;
	return CurrentPosition - ExpectedPosition;
}

FVector AExperimentalCube::ComputeAngularMomentumError() 
{
	FVector CurrentAngularVelocity = CubeMesh->GetPhysicsAngularVelocity() / 100;
	FVector InertiaTensor = CubeMesh->GetInertiaTensor() / 10000;
	CurrentAngularMomentum = InertiaTensor * CurrentAngularVelocity;
	
	return (CurrentAngularMomentum - InitialAngularMomentum) / InitialAngularMomentum.Size();
}

float AExperimentalCube::ComputeEnergyError() 
{
	float CurrentEnergy = ComputeTotalEnergy();
	return (CurrentEnergy - InitialEnergy) / InitialEnergy;
}

void AExperimentalCube::AddObservationLabels() 
{
	// This function adds labels to the ObservationsArray and saves the content of the beforementioned array to a .csv file.
	FString ObservationLabels = FString("Time") + "," + FString("IsComplex") + "," + FString("X Velocity") + "," + FString("Y Velocity") + "," + FString("Z Velocity") + "," +
		FString("X Velocity Error") + "," + FString("Y Velocity Error") + "," + FString("Z Velocity Error") + "," +
		FString("X Position") + "," + FString("Y Position") + "," + FString("Z Position") + "," + FString("X Position Error") + "," + FString("Y Position Error") + "," + FString("Z Position Error") + "," +
		FString("X Angular Momentum") + "," + FString("Y Angular Momentum") + "," + FString("Z Angular Momentum") + "," + FString("X Angular Momentum Error") + "," + FString("Y Angular Momentum Error") + "," + FString("Z Angular Momentum Error") + "," +
		FString("X Angular Velocity") + "," + FString("Y Angular Velocity") + "," + FString("Z Angular Velocity") + "," +
		FString("Energy") + "," + FString("Energy Error") + "," +
		FString("Roll") + "," + FString("Yaw") + "," + FString("Pitch") + ",";

	ObservationsArray.Insert(ObservationLabels, 0);
	ATextFileManager::SaveArrayText(UKismetSystemLibrary::GetProjectDirectory(), FileName, ObservationsArray, true);

	// Modify the value of the auxiliary so that labels are added only once.
	bAddedLabels = true;
}

void AExperimentalCube::AddObservation()
{
	// This function adds an Observation to the ObservationsArray.
	FString Observation = "";
	FVector VelocityVector = CubeMesh->GetComponentVelocity() / 100;

	FVector PositionVector = CubeMesh->GetCenterOfMass() / 100;
	FRotator RotationVector = GetActorRotation();
	FVector AngularVelocityVector = CubeMesh->GetPhysicsAngularVelocity() / 100;

	Observation += FString::SanitizeFloat(CurrentExperimentTime) + ",";
	if (GravityValue.Z >= 0.0f)
	{
		Observation += FString("0") + ",";
	}
	else
	{
		Observation += FString("1") + ",";
	}

	Observation += FString::SanitizeFloat(VelocityVector.X) + "," + FString::SanitizeFloat(VelocityVector.Y) + "," + FString::SanitizeFloat(VelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(LinearVelocityError.X) + "," + FString::SanitizeFloat(LinearVelocityError.Y) + "," + FString::SanitizeFloat(LinearVelocityError.Z) + ",";
	Observation += FString::SanitizeFloat(PositionVector.X) + "," + FString::SanitizeFloat(PositionVector.Y) + "," + FString::SanitizeFloat(PositionVector.Z) + ",";
	Observation += FString::SanitizeFloat(PositionError.X) + "," + FString::SanitizeFloat(PositionError.Y) + "," + FString::SanitizeFloat(PositionError.Z) + ",";
	Observation += FString::SanitizeFloat(CurrentAngularMomentum.X) + "," + FString::SanitizeFloat(CurrentAngularMomentum.Y) + "," + FString::SanitizeFloat(CurrentAngularMomentum.Z) + ",";
	Observation += FString::SanitizeFloat(AngularMomentumError.X) + "," + FString::SanitizeFloat(AngularMomentumError.Y) + "," + FString::SanitizeFloat(AngularMomentumError.Z) + ",";
	Observation += FString::SanitizeFloat(AngularVelocityVector.X) + "," + FString::SanitizeFloat(AngularVelocityVector.Y) + "," + FString::SanitizeFloat(AngularVelocityVector.Z) + ",";
	Observation += FString::SanitizeFloat(ComputeTotalEnergy()) + "," + FString::SanitizeFloat(EnergyError) + ",";
	Observation += FString::SanitizeFloat(RotationVector.Roll) + "," + FString::SanitizeFloat(RotationVector.Yaw) + "," + FString::SanitizeFloat(RotationVector.Pitch) + ",";

	ObservationsArray.Add(Observation);
}

void AExperimentalCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("Frame duration:%f"), DeltaTime);

	FVector ActorLocation = GetActorLocation();
	FVector ComponentLocation = CubeMesh->GetCenterOfMass();

	LinearVelocityError = ComputeLinearVelocityError();

	PositionError = ComputePositionError();

	AngularMomentumError = ComputeAngularMomentumError();

	EnergyError = ComputeEnergyError();

	CurrentExperimentTime += DeltaTime;

	if (CurrentExperimentTime < 10.0f)
	{
		AddObservation();
	}
	else
	{
		if (!bAddedLabels)
		{
			AddObservationLabels();
		}
	}
}

