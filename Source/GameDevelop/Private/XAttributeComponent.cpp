// Fill out your copyright notice in the Description page of Project Settings.


#include "XAttributeComponent.h"

// Sets default values for this component's properties
UXAttributeComponent::UXAttributeComponent()
{
	Health = 100;
}

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}
