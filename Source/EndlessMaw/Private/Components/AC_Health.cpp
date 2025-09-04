// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_Health.h"

void UAC_Health::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp((CurrentHealth - Damage), 0, MaxHealth);
	float ratio = (MaxHealth > 0) ? (CurrentHealth / MaxHealth) : 0;
	if (Damage > 0.f) {
		OnHurt.Broadcast(ratio);
	}
	else {
		OnHeal.Broadcast(ratio);
	}
	if (CurrentHealth <= 0.f) {
		OnDeath.Broadcast();
		GetOwner()->OnTakeAnyDamage.Remove(this, FName("HandleDamage"));
	}
}

// Sets default values for this component's properties
UAC_Health::UAC_Health()
	:MaxHealth(100.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UAC_Health::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UAC_Health::HandleDamage);
}


// Called every frame
void UAC_Health::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

