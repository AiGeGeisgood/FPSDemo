// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XGFPSPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;

UCLASS()
class XGFPS0DEMO_API AXGFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

protected:
	virtual void BeginPlay() override;
};
