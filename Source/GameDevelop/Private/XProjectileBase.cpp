// Fill out your copyright notice in the Description page of Project Settings.


#include "XProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AXProjectileBase::AXProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");

}

// Called when the game starts or when spawned
void AXProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

