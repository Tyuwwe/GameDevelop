// Fill out your copyright notice in the Description page of Project Settings.


#include "XBlackholeProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AXBlackholeProjectile::AXBlackholeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp->SetSphereRadius(32.0f);
	RootComponent = SphereComp;
	
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->Radius = 750.0f;
	
}

// Called when the game starts or when spawned
void AXBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_TimeoutDestroy, this, &AXBlackholeProjectile::destorySelf, 5.0f, false);
}

// Called every frame
void AXBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXBlackholeProjectile::destorySelf()
{
	Destroy();
}



