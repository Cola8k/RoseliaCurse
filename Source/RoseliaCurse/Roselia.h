// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Roselia.generated.h"

UENUM(BlueprintType)
enum class EAnimDirection :uint8
{
	Run_F,
	Run_B,
	Run_L,
	Run_R,
	Idle,
};

UCLASS()
class ROSELIACURSE_API ARoselia : public APaperCharacter
{
	GENERATED_BODY()
	
	

public:
	ARoselia();

	virtual void BeginPlay() override;

	float Speed;
	float SpeedFear;
	float Fear;
	float FearMax;
	bool bIsLightOn;
	FTimerHandle FearManagement_TH;

	UPROPERTY()
	class UPaperSpriteComponent* Torch;

	UPROPERTY()
	class UWorld* MyWorld;

	UFUNCTION()
	void FearManagement();

	UFUNCTION()
	void BerserkMode();

	UFUNCTION()
	void LightSwitch();

	UFUNCTION()
	void CombatStart();

	UFUNCTION()
	void CombatEnd();

	UFUNCTION()
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	
};
