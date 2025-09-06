// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "KismetAnimationLibrary.h"


void UBCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	APawn* pawn = TryGetPawnOwner();
	if (pawn) {
		FVector returnVector = pawn->GetVelocity();
		Velocity = returnVector.Size();
		FRotator returnRotator = pawn->GetActorRotation();
		Direction = UKismetAnimationLibrary::CalculateDirection(returnVector, returnRotator);
	}
	else {
		PreviewWindowUpdate();
	}
}

void UBCAnimInstance::DeathEnded()
{
	OnDeathEnded.Broadcast();
}

void UBCAnimInstance::PreviewWindowUpdate_Implementation()
{
	if (DebugHurt) {
		HurtAnimation();
		DebugHurt = !DebugHurt;
	}
	if (DebugDeath) {
		DeathAnimation();
		DebugDeath = !DebugDeath;
	}
}

void UBCAnimInstance::HurtAnimation_Implementation()
{
	if (HurtAsset) {
		if (!IsAnyMontagePlaying()) {
			PlaySlotAnimationAsDynamicMontage(HurtAsset, SlotName);
		}
	}
}

void UBCAnimInstance::DeathAnimation_Implementation()
{
	int index = FMath::RandHelper(DeathAssetArray.Num());
	if (DeathAssetArray.IsValidIndex(index)) {
		CurrentDeathAsset = DeathAssetArray[index];
	}
	if (CurrentDeathAsset) {
		// if CurrentDeathAsset !=nulltr is the tranisiton rule, set it as output pose in state
		FTimerHandle deathtime;
		// set timer to broadcast DeathEnded() at end of animation
		GetWorld()->GetTimerManager().SetTimer(deathtime, this, 
			&UBCAnimInstance::DeathEnded, CurrentDeathAsset->GetPlayLength());
	}
}

void UBCAnimInstance::SetMoveable(bool ShouldMove)
{
	CanMove = ShouldMove;
}
