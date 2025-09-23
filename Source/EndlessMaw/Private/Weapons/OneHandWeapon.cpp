// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OneHandWeapon.h"
#include "Components/BoxComponent.h"

AOneHandWeapon::AOneHandWeapon()
{
	
}

void AOneHandWeapon::DamageWindowOn()
{
	Super::DamageWindowOn();
}

void AOneHandWeapon::DamageWindowOff()
{
	Super::DamageWindowOff();
}

void AOneHandWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (!Mesh)
		UE_LOG(LogTemp, Error, TEXT("AOneHandWeapon, !Mesh"));
}
