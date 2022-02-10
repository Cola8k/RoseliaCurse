// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_CPP.generated.h"


/**
 * 
 */
UCLASS()
class ROSELIACURSE_API AGM_CPP : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_CPP();
	virtual void BeginPlay() override;

	UPROPERTY()
	class UCameraComponent* CameraPlayer;

	UPROPERTY()
	class USceneComponent* GMRoot;

	UPROPERTY()
	class UWorld* RoseliaWorld;

	UPROPERTY()
	class ACameraPosition_CPP* CameraPositionRef;

	UPROPERTY()
	class APlayerController* RoseliaController;

	UPROPERTY()
	class ARoselia* RoseliaRef;
};
