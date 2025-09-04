// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Health.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealth, float, ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSMAW_API UAC_Health : public UActorComponent
{
	GENERATED_BODY()
	// our current health
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Sets default values for this component's properties
	UAC_Health();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// our max health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// on death delegate
	FOnDeath OnDeath;
	// received healing
	FOnHealth OnHeal;
	// received damage
	FOnHealth OnHurt;
		
};
