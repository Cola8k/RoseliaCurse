// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_CPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "CameraPosition.h"
#include "Roselia.h"
#include "Kismet/GameplayStatics.h"


AGM_CPP::AGM_CPP() 
{
	CameraPlayer=CreateDefaultSubobject<UCameraComponent>("Camera");
}

void AGM_CPP::BeginPlay()
{
	RoseliaWorld = GetWorld();

	CameraRef = RoseliaWorld->SpawnActor<ACameraPosition>(ACameraPosition::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	CameraPlayer->SetWorldLocation(CameraRef->GetActorLocation() + CameraRef->CameraOffset);
	

	RoseliaRef = (ARoselia*)UGameplayStatics::GetActorOfClass(RoseliaWorld, ARoselia::StaticClass());
	if (RoseliaRef)
		RoseliaController = (APlayerController*)RoseliaRef->GetController();
	if (RoseliaController)
		RoseliaController->SetViewTarget(this);

}
