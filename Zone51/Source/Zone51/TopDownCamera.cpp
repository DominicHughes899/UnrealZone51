// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCamera.h"

// Sets default values
ATopDownCamera::ATopDownCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;

	CameraComponent->SetFieldOfView(120.f);

}

// Called when the game starts or when spawned
void ATopDownCamera::BeginPlay()
{
	Super::BeginPlay();

	CameraComponent->AddLocalOffset(FVector(0.f, 0.f, 1000.f)); // -200.f
	CameraComponent->AddLocalRotation(FRotator(-90.f, 0.f, 0.f)); // -80.f

}

// Called every frame
void ATopDownCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATopDownCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

