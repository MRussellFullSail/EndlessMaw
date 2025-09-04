// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BasePlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"


ABasePlayer::ABasePlayer()
	:bCanQueueNextAttack(true), RotateRate(500.f), MaxWalk(600.f), MinAnalog(20.f), 
	CameraBoomLength(400.f), isAttacking(false)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, RotateRate, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->MaxWalkSpeed = MaxWalk;
	GetCharacterMovement()->MinAnalogWalkSpeed = MinAnalog;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraBoomLength; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ABasePlayer::Look(const FInputActionValue& Value) 
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABasePlayer::LightAttack(const FInputActionValue& value)
{
}

void ABasePlayer::HeavyAttack(const FInputActionValue& value)
{
}

void ABasePlayer::AlternateAttack(const FInputActionValue& value)
{
}

void ABasePlayer::Move(const FInputActionValue& Value)
{
	FVector2D moveVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator yaw(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, moveVector.Y);
		AddMovementInput(RightDirection, moveVector.X);
	}
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
		input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayer::Look);
		input->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &ABasePlayer::LightAttack);
		input->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &ABasePlayer::HeavyAttack);
		input->BindAction(AlternateAttackAction, ETriggerEvent::Triggered, this, &ABasePlayer::AlternateAttack);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed input castcheck for baseplayer setupplayerinputcomponent"));
	}
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("No Subsystem for baseplayer beginplay"));
		}
	} 
	else {
		UE_LOG(LogTemp, Error, TEXT("No PlayerController for baseplayer beginplay"));
	}
}
