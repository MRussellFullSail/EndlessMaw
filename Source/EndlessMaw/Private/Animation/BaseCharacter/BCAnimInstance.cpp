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

void UBCAnimInstance::PreviewWindowUpdate_Implementation()
{
}
