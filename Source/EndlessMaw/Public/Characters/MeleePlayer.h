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
};
