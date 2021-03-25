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
#include "ExperimentalCubeFour.generated.h"

class UStaticMeshComponent;

/* This class is used to represent a Cube for experiments in which force patterns are applied to it. */
UCLASS()
class PHYSICSEXPERIMENTS_API AExperimentalCubeFour : public AActor 
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AExperimentalCubeFour();

	virtual void Tick(float DeltaSeconds) override;

	/* Mesh component, used for rendering of the Cube. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	/* Function that adds an Observation to the ObservationsArray. */
	void AddObservation();
	
	/* Function that adds Labels to the existing observations and saves the ObservationsArray to a .csv file. */
	void AddObservationLabels();

	/* Variable holding the name of the file in which the Observations will be saved. */
	FString FileName = "Force_Observations.csv";

	/* Array holding all the Observations and the Labels, its content will be saved as a .csv file. */
	TArray<FString> ObservationsArray;

	/* Auxiliary boolean used to determine if labels were added or not. */
	bool bAddedLabels = false;

	/* Variable holding the experiment duration, therefore deciding the time period for which Observations will be taken. */
	UPROPERTY(EditAnywhere)
	float TotalExperimentDuration = 7.0f;

	/* Variable holding the time elapsed since the experiment began. */
	float CrtTime = 0.0f;

	/* Variable storing the vector representing the force that will be applied to the Cube*/
	FVector ForceVector;

	/* Variable storing an offset from the center of mass of the Cube, deciding where relative to the center of mass the force will be applied. */
	UPROPERTY(EditAnywhere)
	FVector ForceVectorOffset = FVector(0, 0, 0);

	/* Variable holding the force pattern in use. Note that it can be modified from the Editor, therefore running different patterns do not require building the project multiple times. */
	UPROPERTY(EditAnywhere)
	int CurrentForcePattern = 3;

	/* Auxiliary boolean deciding if the experiment is time or tick based. Note that it can be modified from the Editor, switching between time and tick-based experiments do not require building the project multiple times*/
	UPROPERTY(EditAnywhere)
	bool bIsTimeBased = true;

	/* Function that computes the Force that needs to be added at every timestamp, bsased on the CurrentForcePattern. */
	FVector ComputeForceVector(int PatternNumber, float CurrentTime);

	/* Variable holding the duration of the CurrentForcePattern, deciding how long a force is going to be applied to the Cube. */
	UPROPERTY(EditAnywhere)
	float PatternDuration = 5.0f;

	/* Function that computes the Force that needs to be added at every tick, based on the CurrentForcePattern. */
	FVector ComputeTickBasedForce(int PatternNumber, int CurrentIteration);

	/* Function used for Physics Sub-Stepping and tick-based implementation of the force patterns. */
	virtual void PhysicsTick_Implementation(float SubstepDeltaTime);

	/* Delegate used for Physics Sub-stepping. */
	FCalculateCustomPhysics OnCalculateCustomPhysics;

	/* Function used for Physics Sub-Stepping. */
	UFUNCTION(BlueprintNativeEvent)
	void PhysicsTick(float DeltaTime);

	/* Function used for Physics Sub-stepping and tick-based implementation of the force patterns. */
	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance);

	/* Variable holding the number of iterations executed since the experiment began. */
	int CrtIteration = 0;

	/* Variable holding the total number of iterations of the CurrentForcePattern, deciding how many ticks a force is going to be applied to the Cube. */
	UPROPERTY(EditAnywhere)
	int TotalPatternIterations = 5000;

	/* Variable holding the displacement relative to the origin. This is needed so that all experiments can be ran at the same time in one scene, with the obtained results still being relative to the origin. */
	FVector DisplacementVector = FVector(0, 0, 0);

	/* Variable holding the constant force to apply when performing the constant force experiment. */
	UPROPERTY(EditAnywhere)
	float ConstantForce = 20;
};
