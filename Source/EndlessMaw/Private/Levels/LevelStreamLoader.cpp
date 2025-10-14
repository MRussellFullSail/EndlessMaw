// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/LevelStreamLoader.h"
#include "Characters/BasePlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EndlessMaw/EndlessMawGameMode.h"

// Sets default values
ALevelStreamLoader::ALevelStreamLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(BoxCollider);
	BoxCollider->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ALevelStreamLoader::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamLoader::HandleOverlapBegin);
}

void ALevelStreamLoader::HandleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerStartTag.IsEmpty()) return;
	if (LoadLevel.IsNone()) return;
	if (UnloadLevel.IsNone()) return;
	if (ABasePlayer* player = Cast<ABasePlayer>(OtherActor)) {
		Player = player;
		FLatentActionInfo info;
		info.CallbackTarget = this;
		info.ExecutionFunction = "StartLoad";
		info.Linkage = 1;
		UE_LOG(LogTemp, Warning, TEXT("LoadStreamLevel"));
		UGameplayStatics::LoadStreamLevel(GetWorld(), LoadLevel, true, false, info);
	}
}

void ALevelStreamLoader::LoadNewLevel()
{
}

void ALevelStreamLoader::StartLoad()
{
	UE_LOG(LogTemp, Warning, TEXT("StartLoad"));
	AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());
	if (!gamemode) {
		UE_LOG(LogTemp, Error, TEXT("No GameMode"));
		return;
	}
	if (Player == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No Player"));
	}
	FString tag = PlayerStartTag;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tag);
	AActor* location = gamemode->FindPlayerStart(Player->GetController(), *PlayerStartTag);
	Player->SetActorLocation(location->GetActorLocation());
	EndLoad();

}

void ALevelStreamLoader::EndLoad()
{
	UE_LOG(LogTemp, Warning, TEXT("EndLoad"));
	FLatentActionInfo info;
	UGameplayStatics::UnloadStreamLevel(GetWorld(), UnloadLevel, info, false);
}

