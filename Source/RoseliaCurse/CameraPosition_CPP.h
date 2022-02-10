// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraPosition_CPP.generated.h"

UCLASS()
class ROSELIACURSE_API ACameraPosition_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraPosition_CPP();

	UPROPERTY()
	class USceneComponent* CameraPos;
};
