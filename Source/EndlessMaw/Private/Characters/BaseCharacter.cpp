// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "Components/AC_Health.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UBCAnimInstance>(GetMesh()->GetAnimInstance());
	if (!AnimInstance) {
		UE_LOG(LogTemp, Error, TEXT("basecharacter failed to get anim instance"));
		Destroy();
	}
	if (!HealthComponent) {
		UE_LOG(LogTemp, Error, TEXT("basecharacter, !HealthComponent"))
	}
	HealthComponent->OnHurt.AddDynamic(this, &ABaseCharacter::HandleHurt);
	HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeathStart);
}

void ABaseCharacter::HandleHurt(float percent)
{
	AnimInstance->HurtAnimation();
}

void ABaseCharacter::HandleDeathStart()
{
	AnimInstance->DeathAnimation();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

