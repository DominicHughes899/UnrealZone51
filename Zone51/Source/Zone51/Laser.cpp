// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Dynamic Material Instance
	static ConstructorHelpers::FObjectFinder<UMaterial> FadingMaterialComp(TEXT("Material'/Game/Core/Materials/M_FadingRed.M_FadingRed'"));
	if (FadingMaterialComp.Succeeded())
	{
		FadingMaterial = FadingMaterialComp.Object;
	}

	// Setup Warning Triangle
	WarningTriangleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WarningTriangle"));
	RootComponent = WarningTriangleMeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WarningTriangleMeshAsset(TEXT("StaticMesh'/Game/Core/Meshes/SM_Triangle.SM_Triangle'"));
	if (WarningTriangleMeshAsset.Succeeded())
	{
		WarningTriangleMeshComponent->SetStaticMesh(WarningTriangleMeshAsset.Object);
	}

	// Setup Warning Plane
	WarningPlaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WarningPlane"));
	WarningPlaneMeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WarningPlaneMeshAsset(TEXT("StaticMesh'/Game/Core/Meshes/SM_FadingPlane.SM_FadingPlane'"));
	if (WarningPlaneMeshAsset.Succeeded())
	{
		WarningPlaneMeshComponent->SetStaticMesh(WarningPlaneMeshAsset.Object);
	}

	// Setup Laser Beam
	LaserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser"));
	LaserMeshComponent->SetupAttachment(WarningPlaneMeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserMeshAsset(TEXT("StaticMesh'/Game/Core/Meshes/SM_Laser.SM_Laser'"));
	if (LaserMeshAsset.Succeeded())
	{
		LaserMeshComponent->SetStaticMesh(LaserMeshAsset.Object);
	}

	LaserMeshComponent->AddLocalOffset(FVector(0.f, 0.f, 3000.f));
	LaserMeshComponent->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	LaserMeshComponent->ComponentTags.Add("Laser");
	LaserMeshComponent->SetCollisionProfileName("OverlapAll");

}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(StartLocation);

	DynamicFadeMaterial = UMaterialInstanceDynamic::Create(FadingMaterial, this);
	WarningPlaneMeshComponent->SetMaterial(1, DynamicFadeMaterial);
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTimerCounter(DeltaTime);
	UpdateFade();

	AnimateLaser(DeltaTime);

}

void ALaser::Initialize(float WarningDelay, int Size, FVector2D Coords)
{
	DelayTime = WarningDelay;
	LifeTime = DelayTime + 1.f;

	WarningPlaneScale = FVector(WarningPlaneScale.X * Size, WarningPlaneScale.Y * Size, 1.f);

	WarningPlaneMeshComponent->SetWorldScale3D(WarningPlaneScale);

	Coordinates.X -= 100 * Coords.X;
	Coordinates.Y += 100 * Coords.Y;

	AddActorLocalOffset(FVector(Coordinates.X, Coordinates.Y, 0.f));


}

void ALaser::UpdateFade()
{
	fadeValue = FMath::Lerp(0.f, 1.f, LifeTimer / DelayTime);
	DynamicFadeMaterial->SetScalarParameterValue("Percent", fadeValue);
}

void ALaser::AnimateLaser(float DeltaTime)
{
	LaserMeshComponent->AddLocalRotation(FRotator(0.f, LaserRotationRate * DeltaTime, 0.f));

	LaserMeshComponent->AddLocalOffset(FVector(0.f, 0.f, LaserFallSpeed * DeltaTime));

	if (LaserFallSpeed != 0.f)
	{
		CheckInPosition();
	}
}

void ALaser::CheckInPosition()
{
	if (LaserMeshComponent->K2_GetComponentLocation().Z <= 0.f)
	{
		LaserFallSpeed = 0.f;
	}
}

void ALaser::LifeTimerCounter(float DeltaTime)
{
	LifeTimer += DeltaTime;

	if (LifeTimer >= DelayTime && !HasActivated)
	{
		HasActivated = true;
		LaserFallSpeed = -5000.f;
		WarningPlaneMeshComponent->SetVisibility(false);
		WarningTriangleMeshComponent->SetVisibility(false);
	}

	if (LifeTimer >= LifeTime)
	{
		Destroy();
	}
}
