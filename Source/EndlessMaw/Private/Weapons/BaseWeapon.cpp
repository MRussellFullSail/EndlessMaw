// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "Enum/ComboEnum.h"
#include "Characters/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
	:LightDamage(12.f), HeavyDamage(18.f), AlternateDamage(10.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::HandleOverlapBegin);
	Collider->SetActive(false);

	if (!Mesh)
		UE_LOG(LogTemp, Error, TEXT("baseweapon !mesh"));
	if (!Mesh->GetSkeletalMeshAsset())
		UE_LOG(LogTemp, Error, TEXT("baseweapon !mesh->getskeletalmeshasset"));
	Mesh->SetSkeletalMesh(meshasset);
}

void ABaseWeapon::HandleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* owner = Cast<ABaseCharacter>(GetOwner());
	if (!owner) {
		UE_LOG(LogTemp, Error, TEXT("BaseWeapon, !owner"));
		return;
	}
	float damage = 0.f;
	EComboType type = owner->GetComboType();
	if (type == EComboType::Light)
		damage = LightDamage;
	if (type == EComboType::Heavy)
		damage = HeavyDamage;
	if (type == EComboType::Alternate)
		damage = AlternateDamage;
	FDamageEvent damageEvent;
	// dont damage ourselves
	if (OtherActor != Owner) {
		// call take damage on the actor we hit
		OtherActor->TakeDamage(damage, damageEvent, nullptr, this->Owner);
	}
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

