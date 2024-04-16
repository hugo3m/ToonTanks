// Fill out your copyright notice in the Description page of Project Settings.

// always have class include at the top
#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// #include "DrawDebugHelpers.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	// hide actor
	SetActorHiddenInGame(true);
	// disable tick for actor
	SetActorTickEnabled(false);
	bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	// cast parent class to child class
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
		// DrawDebugSphere(
		// 	GetWorld(),
		// 	HitResult.ImpactPoint,
		// 	10.f,
		// 	12,
		// 	FColor::Red,
		// 	false,
		// 	-1.0f
		// );
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// bind axis
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	// bind action
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::MoveForward(float Value)
{
	this->AddActorLocalOffset(FVector(Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), 0, 0), true);
}

void ATank::Turn(float Value)
{
	this->AddActorLocalRotation(FRotator(0, Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this), 0), true);
}

APlayerController* ATank::GetTankPlayerController() const
{
	return TankPlayerController;
}