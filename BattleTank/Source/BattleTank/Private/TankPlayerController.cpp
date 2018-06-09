// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	

	auto Tank = GetControlledTank();
	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank not posessed"));
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Tank %s is posessed by you"), *(Tank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();	
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLoaction(HitLocation)) // Has "side-effect", is going to line trace
	{
		UE_LOG(LogTemp, Error, TEXT("HitLocation: %s"), *HitLocation.ToString());
			// TODO Tell controled tank to aim at this point
	}	
}

// Get world locaiton of line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLoaction(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}
