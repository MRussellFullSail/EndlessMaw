// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OneHandWeapon.h"
#include "Components/BoxComponent.h"

AOneHandWeapon::AOneHandWeapon()
{

}

void AOneHandWeapon::DamageWindowOn()
{
	Collider->SetActive(true);
}

void AOneHandWeapon::DamageWindowOff()
{
	Collider->SetActive(false);
}

void AOneHandWeapon::BeginPlay()
{
	Super::BeginPlay();
}
