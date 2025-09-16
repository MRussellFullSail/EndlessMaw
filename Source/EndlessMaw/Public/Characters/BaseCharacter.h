// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PickupInterface.h"
#include "Enum/ComboEnum.h"
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

	bool bCanQueueNextAttack;
	FName MontageSection;
	EComboType Combo;
	// handle hurt animation
	UFUNCTION()
	virtual void HandleHurt(float percent);
	// handle death animation
	UFUNCTION()
	virtual void HandleDeathStart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MainWeaponSocket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AActor> BaseWeapon;

public:	
	bool isAttacking;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ~Begin IPickupInterface
	virtual bool CanPickupDamage() const override { return false; }
	virtual bool CanPickupHealth() const override { return false; }
	virtual bool CanPickupMaxHealth() const override { return false; }
	// ~End IPickupInterface

	// can the player start the next attack
	inline bool CanQueueNextAttack() const { return bCanQueueNextAttack; }
	// set the player to be able to queue the next attack
	void SetQueueNextAttack(bool canqueue);
	// is player currently attacking
	inline bool IsAttacking() const { return isAttacking; }
	// should we be allowed to move
	bool ShouldMove() const;
	// set the name of the section of the anim montage
	void SetMontageSection(FName section);
	// get the name of the current section of the anim montage
	inline FName GetMontageSection() const { return MontageSection; }
	// what is our current combo type heavy or light
	inline EComboType GetComboType() const { return Combo; }
	// set the the next combo is
	void SetComboType(EComboType type);
};
