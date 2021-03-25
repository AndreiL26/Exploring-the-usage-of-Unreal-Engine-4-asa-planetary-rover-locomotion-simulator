// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Experimental_Sphere.generated.h"

class UStaticMeshComponent;
class UMaterial;
UCLASS()
class ROVER_SIMULATION_API AExperimental_Sphere : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	float CurrentTime = 0.0f;

	TArray<FString> ObservationsArray;

	bool bHasAddedLabels = false;

public:	
	AExperimental_Sphere();

	virtual void Tick(float DeltaTime) override;

	/* Mesh component, used for rendering of the Sphere. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereMesh;

	/* Custom Material used for the Sphere. */
	UPROPERTY(VisibleAnywhere)
	UMaterial* CustomMaterial;
};
