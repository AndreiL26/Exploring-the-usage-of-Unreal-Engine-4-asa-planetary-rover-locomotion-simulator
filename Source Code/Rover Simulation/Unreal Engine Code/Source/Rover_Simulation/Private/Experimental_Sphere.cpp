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


#include "Experimental_Sphere.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMesh.h"
#include "TextFileManager.h"

AExperimental_Sphere::AExperimental_Sphere()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	//SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Shapes/Custom_Sphere.Custom_Sphere")).Object);
	SphereMesh->SetSimulatePhysics(true);
	SphereMesh->SetMassOverrideInKg("SphereMesh", 500.0f, true);
	SetRootComponent(SphereMesh);
	SetPivotOffset(SphereMesh->GetCenterOfMass());
	PrimaryActorTick.bCanEverTick = true;
}

void AExperimental_Sphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExperimental_Sphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentTime < 25.0f) 
	{	
		FString Observation = "";
		FVector VelocityVector = SphereMesh->GetPhysicsLinearVelocity();
		Observation += FString::SanitizeFloat(CurrentTime) + ",";
		//UE_LOG(LogTemp, Warning, TEXT("Sphere velocity: %f %f %f"), VelocityVector.X, VelocityVector.Y, VelocityVector.Z);
		Observation += FString::SanitizeFloat(VelocityVector.X) + "," + FString::SanitizeFloat(VelocityVector.Y) + "," + FString::SanitizeFloat(VelocityVector.Z) + ",";
		ObservationsArray.Add(Observation);
	}
	else if (!bHasAddedLabels)
	{
		FString ObservationLabels = FString("Time") + "," + FString("X Velocity") + "," + FString("Y Velocity") + "," + FString("Z Velocity");
		ObservationsArray.Insert(ObservationLabels, 0);
		ATextFileManager::SaveArrayText(UKismetSystemLibrary::GetProjectDirectory(), "Sphere_Velocity.csv", ObservationsArray, true);

		bHasAddedLabels = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Center of Mass position:%f %f %f"), SphereMesh->GetCenterOfMass().X, SphereMesh->GetCenterOfMass().Y, SphereMesh->GetCenterOfMass().Z);

	CurrentTime += DeltaTime;
}

