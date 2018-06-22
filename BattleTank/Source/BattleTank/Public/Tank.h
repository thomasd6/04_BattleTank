// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel; 
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelRefrence(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretRefrence(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector HitLocation);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local barrel reference to spawn projectiles
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};
