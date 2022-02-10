// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_CPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "CameraPosition.h"
#include "Roselia.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"


AGM_CPP::AGM_CPP() 
{
	GMRoot = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = GMRoot;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraPlayer = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraPlayer->SetupAttachment(CameraArm);
}

void AGM_CPP::BeginPlay()
{
	RoseliaWorld = GetWorld();

	CameraRef = RoseliaWorld->SpawnActor<ACameraPosition>(ACameraPosition::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	CameraPlayer->SetWorldLocation(CameraRef->GetActorLocation() + CameraRef->CameraOffset);
	

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
