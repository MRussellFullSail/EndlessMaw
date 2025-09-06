// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AttackNotifyState.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration)
{
	if (UBCAnimInstance* animInst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance())) {
		animInst->OnDamageWindowStart.Broadcast();
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	if (UBCAnimInstance* animInst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance())) {
		animInst->OnDamageWindowEnd.Broadcast();
	}
}