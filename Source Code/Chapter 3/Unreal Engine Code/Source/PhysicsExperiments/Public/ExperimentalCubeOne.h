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
#include "ExperimentalCubeOne.generated.h"

class UStaticMeshComponent;
class UMaterial;

/* This class is used to represent a Cube for the Gravity Drop Test experiment. */
UCLASS()
class PHYSICSEXPERIMENTS_API AExperimentalCubeOne : public AActor
{
	GENERATED_BODY()
	
public:	
	AExperimentalCubeOne();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/* Mesh component, used for rendering of the Cube. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	/* Custom Material used for the Cube, note that in the original experiments, the Physical Material parameters were: Friction = 0.01, Restitution = 0.0.*/
	UPROPERTY(VisibleAnywhere)
	UMaterial* CustomMaterial;

	/* Variable holding the experiment duration, therefore deciding the time period for which Observations will be taken. */
	UPROPERTY(EditAnywhere)
	float TotalExperimentDuration = 2.0f;

	/* Variable holding the time elapsed since the experiment began. */
	float CurrentTime = 0.0f;

	/* Function that adds an Observation to the ObservationsArray. */
	void AddObservation();

	/* Function that adds Labels to the existing observations and saves the ObservationsArray to a .csv file. */
	void AddObservationLabels();

	/* Array holding all the Observations and the Labels, its content will be saved as a .csv file. */
	TArray<FString> ObservationsArray;

	/* Variable holding the name of the file in which the Observations will be saved. */
	FString FileName = "Gravity_Drop_Test_Observations.csv";

	/* Auxiliary boolean used to determine if labels were added or not. */
	bool bAddedLabels = false;

	/* Variable holding the displacement relative to the origin. This is needed so that all experiments can be ran at the same time in one scene, with the obtained results still being relative to the origin. */
	UPROPERTY(EditAnywhere)
	FVector DisplacementVector = FVector(800.0f, 0, 0);
};
