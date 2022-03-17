// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Roselia.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFearSignature);


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
	float DMGTorch;

	UPROPERTY(BlueprintReadWrite)
	float Fear;

	UPROPERTY(BlueprintReadWrite)
	float FearMax;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsLightOn;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInBerserkMode;

	FTimerHandle FearManagement_TH;
	FTimerHandle DOT_TH;
	FTimerHandle GhostLightDOT_TH;


	UPROPERTY()
	TMap<ETorchDirection, FRotator> TorchRotation;
	
	FRotator Up;
	FRotator Down;
	FRotator Right;
	FRotator Left;
	FCollisionShape TraceShape;


	UPROPERTY(BlueprintAssignable)
	FFearSignature FearDelegate;


	UPROPERTY(EditAnywhere)
	class USpotLightComponent* GhostLight;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* TorchLight;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* Torch;

	UPROPERTY()
	class UWorld* MyWorld;

	UFUNCTION()
	void GHostLightDOT();

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
		
	UFUNCTION()
	void DOT();
	
};
