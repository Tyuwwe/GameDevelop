// Fill out your copyright notice in the Description page of Project Settings.


#include "XMagicProjectile.h"
#include "XAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AXMagicProjectile::AXMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXMagicProjectile::OnActorOverlap);
}

// Called when the game starts or when spawned
void AXMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USphereComponent* AXMagicProjectile::GetSphere()
{
	return SphereComp;
}

void AXMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		UXAttributeComponent* AttributeComp = Cast<UXAttributeComponent>(OtherActor->GetComponentByClass(UXAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
	}
}
