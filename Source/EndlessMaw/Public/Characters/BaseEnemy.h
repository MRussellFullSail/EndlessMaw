// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "BaseEnemy.generated.h"


UCLASS()
class ENDLESSMAW_API ABaseEnemy : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	ABaseEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FName HealthKey;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FName ActionFinished;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class AAIC_Enemy* AIC_Enemy;

	// hook into our custom perception
	UFUNCTION()
	void HandlePerception(AActor* actor, FAIStimulus stimulus);

	// update our blackboard health
	void UpdateBlackboardHealth(float health);

	// handle our hurt
	virtual void HandleHurt(float health) override;
	// handle the end of our death
	UFUNCTION()
	void HandleDeath();
	// handle action being completed
	UFUNCTION()
	void HandleActionFinished();
	UFUNCTION()
	void HandleMontageFinished();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	UAnimMontage* LightAttackMontage;

public:
	virtual void DetermineAttack() override;
	virtual void EnemyLightAttack() override;
	virtual void EnemyHeavyAttack() override;

	FOnMontageEnded EndMontage;
};
