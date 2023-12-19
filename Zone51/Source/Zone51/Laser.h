// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"

#include "Laser.generated.h"

UCLASS()
class ZONE51_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(float WarningDelay, int Size, FVector2D Coords);

	UPROPERTY(EditAnywhere)
	UMaterialInterface* FadingMaterial;

	UMaterialInstanceDynamic* DynamicFadeMaterial;

	// Laser Beam
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh Components")
	UStaticMeshComponent* LaserMeshComponent;

	// Warning Triangle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh Components")
	UStaticMeshComponent* WarningTriangleMeshComponent;

	// Warning Plane
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh Components")
	UStaticMeshComponent* WarningPlaneMeshComponent;

	void UpdateFade();

	FVector WarningPlaneScale = FVector(2.f, 2.f, 1.f);

	// Spawning
	FVector StartLocation = FVector(900.f, -1200.f, 0.f);
	FVector2D Coordinates;

	// Laser
	void AnimateLaser(float DeltaTime);
	void CheckInPosition();

	bool HasActivated = false;
	float LaserRotationRate = 100.f;
	float LaserFallSpeed = 0.f;


	// Else

	void LifeTimerCounter(float DeltaTime);
	float LifeTimer = 0.f;
	float LifeTime = 4.f;

	float fadeValue = 0.f;

	float DelayTime;
	int LaserSize;


};
