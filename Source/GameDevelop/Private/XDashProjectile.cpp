// Fill out your copyright notice in the Description page of Project Settings.


#include "XDashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AXDashProjectile::AXDashProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}
