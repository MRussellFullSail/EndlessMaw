// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/MontageOverState.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void UMontageOverState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	if (UBCAnimInstance* animInst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance())) {
		animInst->OnEndOfMontage.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("montageoverstate"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MontageOverState NotifyEnd, !AnimInstance"));
	}
}