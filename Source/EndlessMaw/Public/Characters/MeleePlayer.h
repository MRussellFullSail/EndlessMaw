// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePlayer.h"
#include "MeleePlayer.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSMAW_API AMeleePlayer : public ABasePlayer
{
	GENERATED_BODY()
	virtual void LightAttack(const FInputActionValue& value) override;
	virtual void HeavyAttack(const FInputActionValue& value) override;
	virtual void AlternateAttack(const FInputActionValue& value) override;
	
protected:
	AMeleePlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	UAnimMontage* LightAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> MovementInstance;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	//TSubclassOf<AActor> MeleeWeapon;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	//class AOneHandWeapon* MainWeapon;

};
