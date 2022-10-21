// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "InteractionFlyPawn.generated.h"


UCLASS(Blueprintable)
class AITURTLES_API AInteractionFlyPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	explicit AInteractionFlyPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	void UpdateInteraction() const;
	void TryInteraction();

private:
	bool LineTraceForInteraction(FHitResult& Hit, ECollisionChannel TraceChannel) const;
};
