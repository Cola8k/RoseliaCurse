// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemySimple_CPP.generated.h"

/**
 * 
 */
UCLASS()
class ROSELIACURSE_API AEnemySimple_CPP : public APaperCharacter
{
	GENERATED_BODY()

	AEnemySimple_CPP();
	

public:

	float HPActual;
	float HPMax;
	FTimerHandle FearSwitch_TH;

	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadWrite)
	bool bIsFeared;

	UFUNCTION()
	virtual void HPManagement(float DMG);
	
	UFUNCTION()
	virtual void LightManagement(float DMG);

	UFUNCTION(BlueprintNativeEvent)
	void FearSwitch();
	void FearSwitch_Implementation();

};
