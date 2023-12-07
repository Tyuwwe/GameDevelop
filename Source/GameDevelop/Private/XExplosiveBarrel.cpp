// Fill out your copyright notice in the Description page of Project Settings.


#include "XExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AXExplosiveBarrel::AXExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh_1 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh_1");
	StaticMesh_1->SetNotifyRigidBodyCollision(true);
	StaticMesh_1->SetSimulatePhysics(true);
	StaticMesh_1->SetCollisionProfileName("PhysicsActor");
	StaticMesh_1->OnComponentHit.AddDynamic(this, &AXExplosiveBarrel::AXOnHit);
	RootComponent = StaticMesh_1;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(StaticMesh_1);
	RadialForceComp->ImpulseStrength = 2500.0;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 750.0;
	RadialForceComp->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AXExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXExplosiveBarrel::AXOnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float NormalImpulseSize = NormalImpulse.Size();
	if (NormalImpulseSize > 20000) RadialForceComp->FireImpulse();
}

void AXExplosiveBarrel::BarrelExplode()
{
	RadialForceComp->FireImpulse();
}


