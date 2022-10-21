// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionFlyPawn.h"

#include "DrawDebugHelpers.h"
#include "Interfaces/InteractionInterface.h"
#include "GameFramework/PlayerController.h"

AInteractionFlyPawn::AInteractionFlyPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bAddDefaultMovementBindings = false;
}

void AInteractionFlyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateInteraction();
}

void AInteractionFlyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward/Backwards", this, &ADefaultPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &ADefaultPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp/Down", this, &ADefaultPawn::MoveUp_World);
	PlayerInputComponent->BindAxis("LookLeft/Right", this, &ADefaultPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp/Down", this, &ADefaultPawn::LookUpAtRate);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ThisClass::TryInteraction);
}

void AInteractionFlyPawn::UpdateInteraction() const
{
	FHitResult HitResult;
	if (LineTraceForInteraction(HitResult, ECC_Visibility))
	{
		if (IsValid(HitResult.GetActor()) && HitResult.GetActor()->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_InteractionFocus(HitResult.GetActor());
		}
	}
}

void AInteractionFlyPawn::TryInteraction()
{
	FHitResult HitResult;
	if (LineTraceForInteraction(HitResult, ECC_Visibility))
	{
		if (IsValid(HitResult.GetActor()) && HitResult.GetActor()->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_Interact(HitResult.GetActor(), this);
		}
	}
}

bool AInteractionFlyPawn::LineTraceForInteraction(FHitResult& Hit, ECollisionChannel TraceChannel) const 
{
	const auto PlayerController = GetController<APlayerController>();
	FVector TraceStart;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(TraceStart, Rotation);

	const FVector TraceEnd = TraceStart + Rotation.Vector() * InteractionDistance;
	return GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel);
}