// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Zone51.h"
#include "Components/CapsuleComponent.h" 
#include "Laser.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacter_Zone51::ACharacter_Zone51()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set character walk speed
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	// Setup Overlap Event delegate
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Zone51::OnCharacterBeginOverlap);
	

}

// Called when the game starts or when spawned
void ACharacter_Zone51::BeginPlay()
{
	Super::BeginPlay();
	

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Zone51::OnOverlapBegin);
	//GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Zone51::OnOverlapBegin);


	SpawnCamera();

}

// Called every frame
void ACharacter_Zone51::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyMovement();

	UpdateEnergy(DeltaTime);



}

// Called to bind functionality to input
void ACharacter_Zone51::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("IAx_MoveUp", this, &ACharacter_Zone51::MoveForward);
	PlayerInputComponent->BindAxis("IAx_MoveRight", this, &ACharacter_Zone51::MoveRight);

	PlayerInputComponent->BindAction("IA_Sprint", IE_Pressed, this, &ACharacter_Zone51::StartSprinting);
	PlayerInputComponent->BindAction("IA_Sprint", IE_Released, this, &ACharacter_Zone51::StopSprinting);
	PlayerInputComponent->BindAction("IA_PT_SpawnLaser", IE_Pressed, this, &ACharacter_Zone51::SpawnLaser);
}

void ACharacter_Zone51::SpawnCamera()
{
	Camera = GetWorld()->SpawnActor<ATopDownCamera>(GetActorLocation(), GetActorRotation());
	GetWorld()->GetFirstPlayerController()->SetViewTarget(Camera);
}

void ACharacter_Zone51::StartSprinting()
{
	IsSprinting = true;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;

}

void ACharacter_Zone51::StopSprinting()
{
	IsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ACharacter_Zone51::UpdateEnergy(float dT)
{
	if (IsSprinting)
	{
		// Calculate new energy
		Energy -= EnergyConsumptionRate * dT;

		UpdateUI();

		// Check if Player can still sprint
		if (Energy <= 0.f)
		{
			StopSprinting();
		}
	}
}

void ACharacter_Zone51::ApplyMovement()
{
	AddMovementInput(MovementInput.GetSafeNormal());
}

void ACharacter_Zone51::SpawnLaser()
{
	ALaser* newLaser = GetWorld()->SpawnActor<ALaser>();

	FVector2D CoordLocation = FVector2D(FMath::RandRange(0, 16), FMath::RandRange(0, 24));

	newLaser->Initialize(3.f, 2, CoordLocation);

}


void ACharacter_Zone51::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("Laser"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Lasered!!!");
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Overlappinggggg");


}

