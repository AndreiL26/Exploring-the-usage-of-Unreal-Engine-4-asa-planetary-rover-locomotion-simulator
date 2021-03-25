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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExperimentalCube.generated.h"

class UStaticMeshComponent;
class UMaterial;

/* Thiss class is used to represent the Cube from the boxes benchmark.*/
UCLASS()
class BENCHMARK_01_API AExperimentalCube : public AActor
{
	GENERATED_BODY()
	
private:
	FVector ComputeLinearVelocityError();

	FVector ComputePositionError();

	FVector ComputeAngularMomentumError();


	float ComputeEnergyError();
	
	float ComputeTotalEnergy();

	float InitialEnergy;
	float CurrentExperimentTime = 0.0f;
	FVector GravityValue;
	FVector InitialPosition;
	FVector InitialAngularMomentum;
	FVector LinearVelocityError;
	FVector PositionError;
	FVector CurrentAngularMomentum;
	FVector AngularMomentumError;
	float EnergyError;

protected:
	virtual void BeginPlay() override;

public:	
	AExperimentalCube();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Mesh component, used for rendering of the Cube. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	// UE4 uses cm/s and gazebo uses m/s, that is why the velocity here is 10 times higher than the one in gazebo.
	UPROPERTY(EditAnywhere)
	FVector InitialLinearVelocity;

	UPROPERTY(EditAnywhere)
	FVector InitialAngularVelocity;

	/* Function that adds an Observation to the ObservationsArray. */
	void AddObservation();

	/* Function that adds Labels to the existing observations and saves the ObservationsArray to a .csv file. */
	void AddObservationLabels();

	/* Variable holding the name of the file in which the Observations will be saved. */
	FString FileName;

	/* Array holding all the Observations and the Labels, its content will be saved as a .csv file. */
	TArray<FString> ObservationsArray;

	/* Auxiliary boolean used to determine if labels were added or not. */
	bool bAddedLabels = false;
};
