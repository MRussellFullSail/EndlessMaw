// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MeleePlayer.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

#include "Weapons/BaseWeapon.h"

#include "Weapons/OneHandWeapon.h"


void AMeleePlayer::LightAttack(const FInputActionValue& value)
{
	if (IsValid(LightAttackMontage)) {
		if (CanQueueNextAttack()) { // can we attack?
			if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) { // no montage is playing, goto the opener
				AnimInstance->Montage_JumpToSection(FName("Opener"), LightAttackMontage);
			}
			// jump to the section to plau
			AnimInstance->Montage_JumpToSection(GetMontageSection(), LightAttackMontage);
			// mark that we are unable to attack
			bCanQueueNextAttack = false;
			AnimInstance->SetMoveable(false);
			isAttacking = true;
			// play the attack
			SetComboType(EComboType::Light);
			PlayAnimMontage(LightAttackMontage, 1.f, MontageSection);
		}
		else if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) { 
			// we cant attack but no montage is playing reset, to the opener
			AnimInstance->Montage_JumpToSection(FName("Opener"), LightAttackMontage);
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
	Super::BeginPlay();
	if (!AnimInstance) {
		UE_LOG(LogTemp, Warning, TEXT("melee has no animinstance"));
	}
	if (!MovementInstance) {
		UE_LOG(LogTemp, Warning, TEXT("melee has no movement"));
	}
	GetMesh()->LinkAnimClassLayers(MovementInstance);
	if (!IsValid(base)) {
		UE_LOG(LogTemp, Error, TEXT("!base"));
		Destroy();
		return;
	}
	if (IsValid(BaseWeapon)) {
		//sword = Cast<AOneHandWeapon>(BaseWeapon);
		//sword = NewObject<AOneHandWeapon>(GetWorld(), base);
		FActorSpawnParameters spawn;
		
		sword = GetWorld()->SpawnActor<AOneHandWeapon>(spawn);
		if (sword != nullptr) {
			sword->SetOwner(this);
			sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
				MainWeaponSocket);
			AnimInstance->OnDamageWindowStart.AddDynamic(sword, &AOneHandWeapon::DamageWindowOn);
			AnimInstance->OnDamageWindowEnd.AddDynamic(sword, &AOneHandWeapon::DamageWindowOff);
			sword->Mesh->SetSkeletalMeshAsset(weaponmesh);
			sword->SetActorRelativeRotation(FRotator(0, -70, 110));
			sword->SetActorScale3D(FVector(.7, .3, .6));
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("MeleePlayer, !sword"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("MeleePlayer, !BaseWeapon"));
	}
}

