// Fill out your copyright notice in the Description page of Project Settings.


#include "XGFPSPlayerController.h"

#include "EnhancedInputSubsystems.h"

void AXGFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	if (Subsystem.Get())
	{
		Subsystem->AddMappingContext(InputMappingContext,0);
	}
}
