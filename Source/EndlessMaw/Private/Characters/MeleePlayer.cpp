// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MeleePlayer.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void AMeleePlayer::LightAttack(const FInputActionValue& value)
{
	//Super::LightAttack();
	if (IsValid(LightAttackMontage)) {
		if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) {
			PlayAnimMontage(LightAttackMontage);
			UE_LOG(LogTemp, Warning, TEXT("meleeplayer light attack montage"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Melee Player, !LightAttackMontage"));
	}
}

void AMeleePlayer::HeavyAttack(const FInputActionValue& value)
{
}

void AMeleePlayer::AlternateAttack(const FInputActionValue& value)
{
}

AMeleePlayer::AMeleePlayer()
{
}

void AMeleePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMeleePlayer::BeginPlay()
{
}

