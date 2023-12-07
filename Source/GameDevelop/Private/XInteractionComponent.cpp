// Fill out your copyright notice in the Description page of Project Settings.


#include "XInteractionComponent.h"
#include "XGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "XCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UXInteractionComponent::UXInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UXInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UXInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UXInteractionComponent::PrimaryInteract() 
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	AXCharacter* MyActor = Cast<AXCharacter>(MyOwner);

	//FVector EyeLocation;
	//FRotator EyeRotation;
	//MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	UCameraComponent* CurrentCam = MyActor->GetCamera();
	FVector CamLocation = CurrentCam->GetComponentLocation();
	FRotator CamRotation = CurrentCam->GetComponentRotation();
	//APawn* MyPawn = Cast<APawn>(MyOwner);
	float SpringArmLength = MyActor->GetSpringArmLength();
	

	FVector End = CamLocation + (CamRotation.Vector() * 500) + (CamRotation.Vector() * SpringArmLength);
	FVector Start = CamLocation + (CamRotation.Vector() * SpringArmLength);
	//FVector End = EyeLocation + (EyeRotation.Vector() * 500);

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.0f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UXGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				IXGameplayInterface::Execute_Interact(HitActor, MyPawn);
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
				break;
			}
		}
	}
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);


	/*
	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<UXGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);

			IXGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
	*/
	
}
