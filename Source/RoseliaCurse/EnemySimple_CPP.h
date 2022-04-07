// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemySimple_CPP.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(RemoveFromArraySignature, class AEnemySimple_CPP*);

UCLASS()
class ROSELIACURSE_API AEnemySimple_CPP : public APaperCharacter
{
	GENERATED_BODY()

	AEnemySimple_CPP();
	

public:

	bool bCanTakeDMG;

	float HPActual;
	float HPMax;
	FTimerHandle FearSwitch_TH;
	FTimerHandle DMGReset_TH;

	virtual void BeginPlay() override;

	RemoveFromArraySignature RemoveFromArrayDelegate;

	UPROPERTY(BlueprintReadWrite)
	bool bIsFeared;

	UFUNCTION()
	virtual void HPManagement(float DMG);

	UFUNCTION()
	virtual void DMGReset();
	
	UFUNCTION()
	virtual void LightManagement(float DMG);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FearSwitch();
	void FearSwitch_Implementation();



};
