// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XProjectileBase.h"
#include "XBlackholeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class GAMEDEVELOP_API AXBlackholeProjectile : public AXProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXBlackholeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	FTimerHandle TimerHandle_TimeoutDestroy;

	FOverlapInfo OverlappedItems;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void destorySelf();

};
