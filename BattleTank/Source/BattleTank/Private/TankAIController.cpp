// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI: Player Tank not found"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI: I have found player tank %s"), *(PlayerTank->GetName()));
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank =GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerTank);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{ 
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	
}