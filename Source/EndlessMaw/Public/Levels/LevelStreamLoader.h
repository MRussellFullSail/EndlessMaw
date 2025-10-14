// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamLoader.generated.h"

UCLASS()
class ENDLESSMAW_API ALevelStreamLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelStreamLoader();

	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<class ABasePlayer> Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loading")
	class UBoxComponent* BoxCollider;

public:	
	UPROPERTY(EditAnywhere, Category = "Loading")
	FName LoadLevel;
	UPROPERTY(EditAnywhere, Category = "Loading")
	FName UnloadLevel;
	UPROPERTY(EditAnywhere, Category = "Loading")
	FString PlayerStartTag;

	UFUNCTION()
	void HandleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void LoadNewLevel();
	UFUNCTION(BlueprintCallable)
	void StartLoad();
	UFUNCTION(BlueprintCallable)
	void EndLoad();
};
