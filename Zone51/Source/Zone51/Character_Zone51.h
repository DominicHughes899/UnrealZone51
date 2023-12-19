// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "TopDownCamera.h"

#include "Character_Zone51.generated.h"

UCLASS()
class ZONE51_API ACharacter_Zone51 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Zone51();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ==== Camera ====
	void SpawnCamera();

	ATopDownCamera* Camera;

	// ==== Movement ====
	void MoveForward(float Value) { MovementInput.X = Value; }
	void MoveRight(float Value) { MovementInput.Y = Value; }

	void StartSprinting();
	void StopSprinting();
	void UpdateEnergy(float dT);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateUI();

	UFUNCTION(BlueprintCallable)
	float GetEnergyLevel() { return Energy; }

	void ApplyMovement();

	FVector MovementInput;

	bool IsSprinting = false;
	bool CanSprint = true;
	float Energy = 1.f;
	float EnergyConsumptionRate = .2f;

	// ==== Laser ====
	void SpawnLaser();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


};
