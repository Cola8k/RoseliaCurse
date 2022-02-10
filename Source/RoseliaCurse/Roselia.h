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

UENUM(BlueprintType)
enum class ETorchDirection :uint8
{
	Up,
	Down,
	Left,
	Right,

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

	UPROPERTY(BlueprintReadOnly)
	float Fear;

	UPROPERTY(BlueprintReadOnly)
	float FearMax;
		
	bool bIsLightOn;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInBerserkMode;

	FTimerHandle FearManagement_TH;

	UPROPERTY()
		TMap<ETorchDirection, FRotator> TorchRotation;
	
	FRotator Up;
	FRotator Down;
	FRotator Right;
	FRotator Left;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* TorchLight;

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
	void MoveRight(float Value);

	UFUNCTION()
	void MoveUp(float Value);

	UFUNCTION()
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	
};
