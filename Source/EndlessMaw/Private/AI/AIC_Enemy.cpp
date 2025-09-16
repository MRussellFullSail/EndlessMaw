// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIC_Enemy.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"


void AAIC_Enemy::HandlePerception(AActor* actor, FAIStimulus stimulus)
{
	OnPerception.Broadcast(actor, stimulus);
}

AAIC_Enemy::AAIC_Enemy()
	:PlayerKey("Player"), LocationKey("Location")
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

}

void AAIC_Enemy::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	// run the given behavior tree
	if (ABaseEnemy* enemy = Cast<ABaseEnemy>(pawn)) {
		if (enemy->BehaviorTree)
			RunBehaviorTree(enemy->BehaviorTree);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIC_Enemy OnPossess, failed enemy cast"));
		Destroy();
		return;
	}
	// register our config
	if (Sight && Perception) {
		Perception->ConfigureSense(*Sight);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIC_Enemy OnPossess, no Sight or Perception"));
		Destroy();
		return;
	}
}

void AAIC_Enemy::BeginPlay()
{
	Super::BeginPlay();
	if (Perception) {
		Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Enemy::HandlePerception);
	}

}
