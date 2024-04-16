// Fill out your copyright notice in the Description page of Project Settings.
// tower.h always first
#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // if tank exists
    if(IsTankInRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle,
        this,
        &ATower::CheckFireCondition,
        FireRate,
        true
        );
}

void ATower::CheckFireCondition()
{  
    if(!Tank)
    {
        return;
    }
    if(Tank->bAlive && IsTankInRange())
    {
        Fire();
    }
}

bool ATower::IsTankInRange()
{
    if(Tank)
    {
        // find distance to the tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        // if in range
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}
