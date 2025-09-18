// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "Components/AC_Health.h"
#include "Weapons/BaseWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
	:bCanQueueNextAttack(true), isAttacking(false), MontageSection(NAME_None), isDead(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	HealthComponent = CreateDefaultSubobject<UAC_Health>(TEXT("Health Component"));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90.0));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UBCAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->OnDeathEnded.AddDynamic(this, &ABaseCharacter::HandleDeath);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("basecharacter failed to get anim instance"));
		Destroy();
		return;
	}
	if (HealthComponent) {
		HealthComponent->OnHurt.AddDynamic(this, &ABaseCharacter::HandleHurt);
		HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeathStart);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("basecharacter, !HealthComponent"));
		Destroy();
		return;
	}

}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type Reason)
{
	if (AnimInstance) {
		AnimInstance->OnDeathEnded.RemoveAll(this);
		AnimInstance->OnMontageEnded.RemoveAll(this);
	}
	if (HealthComponent) {
		HealthComponent->OnHurt.RemoveAll(this);
		HealthComponent->OnDeath.RemoveAll(this);
	}
	Super::EndPlay(Reason);
}

void ABaseCharacter::HandleHurt(float percent)
{
	AnimInstance->HurtAnimation();
}

void ABaseCharacter::HandleDeathStart()
{
	AnimInstance->DeathAnimation();
}

void ABaseCharacter::HandleDeath()
{
	if (isDead) return;
	isDead = true;
	SetActorTickEnabled(false);
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopActiveMovement();
	SetActorEnableCollision(false);
	if (AnimInstance) {
		AnimInstance->StopAllMontages(1.f);
	}
	Destroy();
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::SetQueueNextAttack(bool canqueue)
{
	bCanQueueNextAttack = canqueue;
}

bool ABaseCharacter::ShouldMove() const
{
	return !isAttacking && !AnimInstance->IsAnyMontagePlaying();
}

void ABaseCharacter::SetMontageSection(FName section)
{
	MontageSection = section;
}

void ABaseCharacter::SetComboType(EComboType type)
{
	Combo = type;
}