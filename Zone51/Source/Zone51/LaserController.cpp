// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserController.h"

// Sets default values
ALaserController::ALaserController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer(DeltaTime);

}

void ALaserController::Timer(float DeltaTime)
{
	TimeElapsed += DeltaTime;
}

