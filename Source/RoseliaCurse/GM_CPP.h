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
	


	UPROPERTY(BlueprintReadWrite)
	class UCameraComponent* CameraPlayer;

	UPROPERTY()
	class USceneComponent* GMRoot;

	UPROPERTY()
	class UWorld* RoseliaWorld;

	UPROPERTY()
	class ACameraPosition_CPP* CameraPositionRef;

	UPROPERTY(BlueprintReadWrite)
	class APlayerController* RoseliaController;

	UPROPERTY(BlueprintReadWrite)
	class ARoselia* RoseliaRef;

	UPROPERTY(EditAnywhere)
	TArray<class AEnemySimple_CPP*> EnemyArray;

	UFUNCTION()
	void RemoveFromArray(class AEnemySimple_CPP* EnemyRef);

	UFUNCTION()
	void SetupEnemyArray(class AEnemySimple_CPP* EnemyRef);

	UFUNCTION(BlueprintPure)
	class UCameraComponent* GetCameraPleyer() { return CameraPlayer; }

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnBoss();

	UFUNCTION(BlueprintImplementableEvent)
		void OpenRoom();

	UFUNCTION(BlueprintImplementableEvent)
		void DestroyBossEnemy();
};
