// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "QueueAttackNotifyState.generated.h"

UENUM()
enum EComboSection {
	None		UMETA(DisplayName = "None"),
	Opener		UMETA(DisplayName = "Opener"),
	Follow1		UMETA(DisplayName = "Follow1")
};

UCLASS()
class ENDLESSMAW_API UQueueAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* meshComp,
		UAnimSequenceBase* animation, float totalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation) override;

public:
	FName NextSection = NAME_None;
	TEnumAsByte<EComboSection> ComboSection;
};
