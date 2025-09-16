// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIC_Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPerception, AActor*, Actor, FAIStimulus, Stimulus);


UCLASS()
class ENDLESSMAW_API AAIC_Enemy : public AAIController
{
	GENERATED_BODY()
	
	// hook into OnTargetPerceptionUpdated
	UFUNCTION()
	void HandlePerception(AActor* actor, FAIStimulus stimulus);

public:
	AAIC_Enemy();

	FPerception OnPerception;
	FName PlayerKey;
	FName LocationKey;

protected:
	virtual void OnPossess(APawn* pawn) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	UAIPerceptionComponent* Perception;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	class UAISenseConfig_Sight* Sight;
};
