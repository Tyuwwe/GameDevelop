// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XAttributeComponent.h"
#include "GameFramework/Character.h"
#include "XInteractionComponent.h"
#include "XCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UXInteractionComponent;
class UAnimMontage;
class UXAttributeComponent;

UCLASS()
class GAMEDEVELOP_API AXCharacter : public ACharacter
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere, Category = "Preload")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Preload")
	TSubclassOf<AActor> ProjectileBlackholeClass;

	UPROPERTY(EditAnywhere, Category = "Preload")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Preload")
	TSubclassOf<AActor> DashProjectileClass;

	AActor* LastProjectile;

	FTimerHandle TimerHandle_PrimaryAttack;

	FTimerHandle TimerHandle_SecondaryAttack;
	
	FTimerHandle TimerHandle_Dash;

	FTimerHandle TimerHandle_DashTransform;

public:
	// Sets default values for this character's properties
	AXCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UXInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UXAttributeComponent* AttributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void PrimaryAttack();

	void PlayerJump();
	
	void PrimaryInteract();

	void PrimaryAttack_TimeElapsed(TSubclassOf<AActor> Projectile);

	void SecondaryAttack();

	void PlayerDash();

	void PlayerDash_TimeElapsed();

public:
	float GetSpringArmLength();

	UCameraComponent* GetCamera();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
