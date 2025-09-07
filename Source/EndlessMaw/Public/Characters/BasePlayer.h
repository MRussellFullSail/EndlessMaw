// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enum/ComboEnum.h"
#include "BasePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDelegate);

UCLASS()
class ENDLESSMAW_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	ABasePlayer();
	// wasd movement
	void Move(const struct FInputActionValue& Value);
	// look with mouse x
	void Look(const FInputActionValue& Value);
	// light attack, override in individual classes
	virtual void LightAttack(const FInputActionValue& value);
	// heavy attack, override in individual classes
	virtual void HeavyAttack(const FInputActionValue& value);
	// alternate attack, override in individual classes
	virtual void AlternateAttack(const FInputActionValue& value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraBoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LightAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* HeavyAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* AlternateAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxWalk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinAnalog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotateRate;

	bool bCanQueueNextAttack;
	bool isAttacking;
	FName MontageSection;
	EComboType Combo;

public:
	// can the player start the next attack
	inline bool CanQueueNextAttack() const { return bCanQueueNextAttack; }
	// set the player to be able to queue the next attack
	void SetQueueNextAttack(bool canqueue);
	// is player currently attacking
	inline bool IsAttacking() const { return isAttacking; }
	// set the name of the section of the anim montage
	void SetMontageSection(FName section);
	// get the name of the current section of the anim montage
	inline FName GetMontageSection() const { return MontageSection; }
	// what is our current combo type heavy or light
	inline EComboType GetComboType() const { return Combo; }
	// set the the next combo is
	void SetComboType(EComboType type);

	// player delegate for their death
	FPlayerDelegate OnPlayerDeath;

	// ~Begin IPickupInterface
	virtual bool CanPickupHealth() const override { return true; }
	virtual bool CanPickupDamage() const override { return true; }
	virtual bool CanPickupMaxHealth() const override { return true; }
	// ~End IPickupInterface

};
