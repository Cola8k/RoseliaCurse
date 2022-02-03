// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraPosition.generated.h"

UCLASS()
class ROSELIACURSE_API ACameraPosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraPosition();


	UPROPERTY()
	FVector CameraOffset;

	UPROPERTY()
	class UStaticMeshComponent* Floor;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
