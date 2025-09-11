// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::HandleOverlapBegin);
}

void ABaseWeapon::DamageWindowOn()
{
	Collider->SetActive(true);
}

void ABaseWeapon::DamageWindowOff()
{
	Collider->SetActive(false);
}

void ABaseWeapon::HandleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent damageEvent;
	OtherActor->TakeDamage(10.f, damageEvent, nullptr, this->Owner);
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

