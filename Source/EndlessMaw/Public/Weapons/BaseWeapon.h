// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"


UCLASS()
class ENDLESSMAW_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	class UBoxComponent* Collider;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	USkeletalMesh* meshasset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LightDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float HeavyDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float AlternateDamage;

	UFUNCTION()
	void HandleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float CurrentDamage;
	float ComboBonusDamage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
