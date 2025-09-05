// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PickupInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ENDLESSMAW_API ABaseCharacter : public ACharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// our anim instance
	class UBCAnimInstance* AnimInstance;
	// our health component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	class UAC_Health* HealthComponent;

	// handle hurt animation
	UFUNCTION()
	virtual void HandleHurt(float percent);
	// handle death animation
	UFUNCTION()
	virtual void HandleDeathStart();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ~Begin IPickupInterface
	virtual bool CanPickupDamage() const override { return false; }
	virtual bool CanPickupHealth() const override { return false; }
	// ~End IPickupInterface

};
