// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSMAW_API UAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* meshComp,
		UAnimSequenceBase* animation, float totalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation) override;
};
