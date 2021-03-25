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
#include "Basic_Rover.generated.h"

class UStaticMeshComponent;
class UMaterial;
class USceneComponent;
class UPhysicsConstraintComponent;

/* Thiss class is used to represent a basic rover containing one box placed on top of 4 cylinders acting as wheels.*/
UCLASS()
class ROVER_SIMULATION_API ABasic_Rover : public AActor
{
	GENERATED_BODY()
	
private:
	
	USceneComponent* DummnyRootComponent;

	void AttachWheel(UStaticMeshComponent* Wheel, FVector RelativeLocation);

	void SetupConstraint(UStaticMeshComponent* Wheel, UPhysicsConstraintComponent* Constraint, FVector RelativeLocation);

	void LogObservations();

	void AddObservation(TArray<FString>* ObservationsArray, UStaticMeshComponent* Mesh);

	void AddLabels();

	float TotalTime = 15.0f;
	
	float CurrentTime = 0.0f;

	bool bHasAppliedForce = true;

	bool bHasAddedLabels = false;

	TArray<FString> FrontLeftWheelObservations;
	TArray<FString> FrontRightWheelObservations;
	TArray<FString> BackLeftWheelObservations;
	TArray<FString> BackRightWheelObservations;
	TArray<FString> ChassisObservations;

protected:
	virtual void BeginPlay() override;

public:	
	ABasic_Rover();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Mesh component representing the chassis of the rover. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RoverChassis;

	/* Mesh component representing the front left wheel of the rover. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrontLeftWheel;

	/* Mesh component representing the front right wheel of the rover. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrontRightWheel;

	/* Mesh component representing the back left wheel of the rover. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BackLeftWheel;

	/* Mesh component representing the back right wheel of the rover. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BackRightWheel;

	/* Physics constraint used to represent the joint between the front left wheel and the rover chassis.*/
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* FrontLeftWheel_Constraint;

	/* Physics constraint used to represent the joint between the front right wheel and the rover chassis.*/
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* FrontRightWheel_Constraint;

	/* Physics constraint used to represent the joint between the back left wheel and the rover chassis.*/
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* BackLeftWheel_Constraint;

	/* Physics constraint used to represent the joint between the back right wheel and the rover chassis.*/
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* BackRightWheel_Constraint;

	UPROPERTY(EditAnywhere)
	FVector ForceToApply;
};
