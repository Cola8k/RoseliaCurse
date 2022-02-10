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
#include "Components/SpotLightComponent.h"


ARoselia::ARoselia() 
{

	// Setup Param
	Speed = 300;
	Fear = 1;
	FearMax = 100;
	SpeedFear = 600;
	bIsInBerserkMode = false;
	
	

	//Setup Torch
	ConstructorHelpers::FObjectFinder<UPaperSprite>TorchAsset(TEXT("PaperSprite'/Game/Torch.Torch'"));
	Torch = CreateDefaultSubobject<UPaperSpriteComponent>("TorchSprite");
	Torch->SetSprite(TorchAsset.Object);
	TorchLight = CreateDefaultSubobject<USpotLightComponent>("TorchLight");
	TorchLight->SetupAttachment(RootComponent);
	
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

	Left = FRotator(0, 270, 0);
	Right = FRotator(0, 90, 0);
	TorchRotation.Add(ETorchDirection::Left, Left);
	TorchRotation.Add(ETorchDirection::Right, Right);


	Up = FRotator(0, 0, 0);
	Down = FRotator(0, 180, 0);
	TorchRotation.Add(ETorchDirection::Up, Up);
	TorchRotation.Add(ETorchDirection::Down, Down);
	
	
	
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
	if (!bIsInBerserkMode)
	{
		if (Fear < FearMax)
		{
			if (bIsLightOn)
				Fear++;
			else
				Fear += 1.5f;
		}
		else
		{
			BerserkMode();
		}
	}
	else 
	{
		if (Fear > 0) 
		{
			Fear -= 2.5f;
		}
		else
		{
			bIsInBerserkMode = false;
		}

	}
}

void ARoselia::BerserkMode()
{
	bIsInBerserkMode = true;
	

}

void ARoselia::LightSwitch()
{
	if (bIsLightOn) 
	{
		bIsLightOn = false;
		TorchLight->SetIntensity(0);
	}

	else 
	{
		bIsLightOn = true;
		TorchLight->SetIntensity(100000.f);
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
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Value);

	AddMovementInput(FVector::XAxisVector, Value);

	if (Value > 0)
	{
		
		TorchLight->SetWorldRotation(*TorchRotation.Find(ETorchDirection::Up));
		
	}
	else if (Value < 0)
	{
		
		TorchLight->SetWorldRotation(*TorchRotation.Find(ETorchDirection::Down));
	}

}


void ARoselia::MoveRight(float Value)
{
	AddMovementInput(FVector::YAxisVector, Value);
	if (Value > 0)
	{
		TorchLight->SetWorldRotation(*TorchRotation.Find(ETorchDirection::Right));
	}
	else if(Value<0)
		TorchLight->SetWorldRotation(*TorchRotation.Find(ETorchDirection::Left));
}



