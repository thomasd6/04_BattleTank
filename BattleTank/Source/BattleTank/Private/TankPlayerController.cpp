// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	

	auto Tank = GetPlayerTank();
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


ATank* ATankPlayerController::GetPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPlayerTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLoaction(HitLocation)) // Has "side-effect", is going to line trace
	{		
		GetPlayerTank()->AimAt(HitLocation);
	}	
}

// Get world locaiton of line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLoaction(FVector& HitLocation) const
{
	// Find the crosshair postion in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}