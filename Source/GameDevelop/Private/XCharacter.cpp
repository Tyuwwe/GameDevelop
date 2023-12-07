// Fill out your copyright notice in the Description page of Project Settings.


#include "XCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "XInteractionComponent.h"

// Sets default values
AXCharacter::AXCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UXInteractionComponent>("InteractionComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXCharacter::MoveForward(float Value)
{

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AXCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVec = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVec, Value);
}
// Called every frame
void AXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AXCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AXCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AXCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &AXCharacter::PlayerJump);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AXCharacter::PrimaryInteract);
}

void AXCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AXCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AXCharacter::PlayerJump()
{
	Super::Jump();
}

void AXCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
		
}

void AXCharacter::PrimaryAttack_TimeElapsed()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator CamRotation = CameraComp->GetComponentRotation();
	FVector CamLocation = CameraComp->GetComponentLocation() + CamRotation.Vector() * SpringArmComp->TargetArmLength;

	FVector EndLocation = CamLocation + CamRotation.Vector() * 1000;
	FVector AimLocation = EndLocation;

	TArray<FHitResult> Hits;
	float Radius = 30.0f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	bool bCanHit = GetWorld()->SweepMultiByObjectType(Hits, CamLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bCanHit ? FColor::Green : FColor::Red;
	
	for (FHitResult Hit : Hits)
	{
		if(bCanHit)
		{
			AimLocation = Hit.ImpactPoint;
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
			break;
		}
	}

	FVector LookAtVector = AimLocation - HandLocation;
	FRotator LookAtRotation = LookAtVector.Rotation();
	
	DrawDebugLine(GetWorld(), CamLocation, AimLocation, LineColor, false, 2.0f, 0, 2.0f);
	FTransform SpawnTM = FTransform(LookAtRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	
	//AActor* SpawnedActor =  GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	//AXMagicProjectile* SpawnedBall = Cast<AXMagicProjectile>(SpawnedActor);

	//USphereComponent* SpawnedBallSphere = SpawnedBall->GetSphere();
	//SpawnedBallSphere->SetPhysicsLinearVelocity(CameraComp->GetComponentRotation().Vector()*100);
}

float AXCharacter::GetSpringArmLength()
{
	return SpringArmComp->TargetArmLength;
}

UCameraComponent* AXCharacter::GetCamera()
{
	return CameraComp;
}
