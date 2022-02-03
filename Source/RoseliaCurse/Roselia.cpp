// Fill out your copyright notice in the Description page of Project Settings.


#include "Roselia.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"



ARoselia::ARoselia() 
{

	// Setup Param
	Speed = 300;
	Fear = 0;
	FearMax = 100;
	SpeedFear = 600;

	//Setup Torch
	ConstructorHelpers::FObjectFinder<UPaperSprite>TorchAsset(TEXT("PaperSprite'/Game/Torch.Torch'"));
	Torch = CreateDefaultSubobject<UPaperSpriteComponent>("TorchSprite");
	Torch->SetSprite(TorchAsset.Object);
	
	//Setup Roselia
	ConstructorHelpers::FObjectFinder<UPaperFlipbook>RoseliaAsset(TEXT("PaperFlipbook'/Game/Roselia_FB.Roselia_FB'"));
	GetSprite()->SetFlipbook(RoseliaAsset.Object);
	RootComponent = GetCapsuleComponent();	
	Torch->SetupAttachment(RootComponent);
	GetSprite()->SetupAttachment(RootComponent);


	//Setup OtherComponents
}

void ARoselia::BeginPlay()
{
	Super::BeginPlay();


	MyWorld = GetWorld();
	CombatStart();


}


void ARoselia::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LightSwitch", EInputEvent::IE_Pressed, this, &ARoselia::LightSwitch);

	PlayerInputComponent->BindAxis("MoveUp", this, &ARoselia::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARoselia::MoveRight);


}

void ARoselia::FearManagement()
{
	if (Fear < FearMax)
	{
		Fear++;
		UE_LOG(LogTemp, Warning, TEXT("%f"), Fear);
	}
	else
	{
		BerserkMode();
	}

}

void ARoselia::BerserkMode()
{
	MyWorld->GetTimerManager().ClearTimer(FearManagement_TH);
	UE_LOG(LogTemp, Warning, TEXT("Berserk"));

}

void ARoselia::LightSwitch()
{
	if (bIsLightOn) 
	{
		bIsLightOn = false;
		UE_LOG(LogTemp, Warning, TEXT("Light is Off"));
	}

	else 
	{
		bIsLightOn = true;
		UE_LOG(LogTemp, Warning, TEXT("Light is On"));
	}

}

void ARoselia::CombatStart()
{
	
	MyWorld->GetTimerManager().SetTimer(FearManagement_TH, this, &ARoselia::FearManagement, 0.1f, true);
}

void ARoselia::CombatEnd()
{
}

void ARoselia::MoveUp(float Value)
{
	AddMovementInput(FVector::XAxisVector, Value);

}


void ARoselia::MoveRight(float Value)
{
	AddMovementInput(FVector::YAxisVector, Value);

}



