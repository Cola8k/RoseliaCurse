// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_CPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "CameraPosition_CPP.h"
#include "Roselia.h"
#include "EnemySimple_CPP.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"


AGM_CPP::AGM_CPP() 
{
	GMRoot = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = GMRoot;

	CameraPlayer = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraPlayer->SetupAttachment(RootComponent);
}

void AGM_CPP::BeginPlay()
{
	RoseliaWorld = GetWorld();

	CameraPositionRef = (ACameraPosition_CPP*)UGameplayStatics::GetActorOfClass(RoseliaWorld, ACameraPosition_CPP::StaticClass());

	CameraPlayer->SetWorldLocation(CameraPositionRef->GetActorLocation());
	CameraPlayer->SetWorldRotation(CameraPositionRef->GetActorRotation());
	

	RoseliaRef = (ARoselia*)UGameplayStatics::GetActorOfClass(RoseliaWorld, ARoselia::StaticClass());

	if(RoseliaRef)
		UE_LOG(LogTemp, Warning, TEXT("ok"))
	else
		UE_LOG(LogTemp, Warning, TEXT("no"))

	if (RoseliaRef)
		RoseliaController = (APlayerController*)RoseliaRef->GetController();
	if (RoseliaController)
		RoseliaController->SetViewTarget(this);

}

void AGM_CPP::RemoveFromArray(AEnemySimple_CPP* EnemyRef)
{
	EnemyArray.Remove(EnemyRef);
	if (EnemyArray.Num() == 0)
	{
		OpenRoom();
		if (EnemyRef->ActorHasTag("Tentacle"))
		{
			DestroyBossEnemy();
		}
	}
}

void AGM_CPP::SetupEnemyArray(AEnemySimple_CPP* EnemyRef)
{
	EnemyArray.Add(EnemyRef);
	EnemyRef->RemoveFromArrayDelegate.BindUObject(this, &AGM_CPP::RemoveFromArray);

}
