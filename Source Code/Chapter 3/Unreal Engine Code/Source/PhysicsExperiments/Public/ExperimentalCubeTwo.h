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
#include "ExperimentalCubeTwo.generated.h"

class UStaticMeshComponent;
class UMaterial;

/* This class is used to represent a Cube for experiments in which a force is applied only once. */
UCLASS()
class PHYSICSEXPERIMENTS_API AExperimentalCubeTwo : public AActor 
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AExperimentalCubeTwo();

	virtual void Tick(float DeltaSeconds) override;

	/* Mesh component, used for rendering of the Cube. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	/* Custom Material used for the Cube, note that in the original experiments, the Physical Material parameters were: Friction = 0.01, Restitution = 0.0.*/
	UPROPERTY(VisibleAnywhere)
	UMaterial* CustomMaterial;

	/* Function that adds an Observation to the ObservationsArray. */
	void AddObservation();

	/* Function that adds Labels to the existing observations and saves the ObservationsArray to a .csv file. */
	void AddObservationLabels();

	/* Array holding all the Observations and the Labels, its content will be saved as a .csv file. */
	TArray<FString> ObservationsArray;

	/* Variable holding the name of the file in which the Observations will be saved. */
	FString FileName = "Impulse_Observations.csv";

	/* Auxiliary boolean used to determine if labels were added or not. */
	bool bAddedLabels = false;

	/* Variable storing the vector representing the force that will be applied to the Cube*/
	UPROPERTY(EditAnywhere)
	FVector ForceVector;

	/* Variable storing an offset from the center of mass of the Cube, deciding where relative to the center of mass the force will be applied. */
	UPROPERTY(EditAnywhere)
	FVector ForceVectorOffset = FVector(0,0,0);

	/* Variable holding the experiment duration, therefore deciding the time period for which Observations will be taken. */
	UPROPERTY(EditAnywhere)
	float TotalExperimentDuration = 5.0f;

	/* Variable holding the time elapsed since the experiment began. */
	float CrtTime = 0.0f;

	/* Auxiliary boolean used to determine if the force was yet applied. */
	bool bHasAppliedForce = false;

	/* Auxiliary boolean used to determine if the experiment is based on the impulse approach or on the force approach. */
	UPROPERTY(EditAnywhere)
	bool bIsImpulseBased = false;

	/* Variable holding the displacement relative to the origin. This is needed so that all experiments can be ran at the same time in one scene, with the obtained results still being relative to the origin. */
	UPROPERTY(EditAnywhere)
	FVector DisplacementVector = FVector(0, 0, 0);
};
