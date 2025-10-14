// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AttackNotifyState.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration)
{
	if (UBCAnimInstance* animInst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance())) {
		animInst->OnDamageWindowStart.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("attack notify state damage window start"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AttackNotifyState NotifyBegin, !AnimInstance"));
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	if (UBCAnimInstance* animInst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance())) {
		//UE_LOG(LogTemp, Warning, TEXT("attack notify state damage window end"));
		animInst->OnDamageWindowEnd.Broadcast();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AttackNotifyState NotifyEnd, !AnimInstance"));
	}
}