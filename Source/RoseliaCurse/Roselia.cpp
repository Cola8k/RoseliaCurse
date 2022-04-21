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
#include "EnemySimple_CPP.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ARoselia::ARoselia() 
{

	// Setup Param
	Speed = 300;
	Fear = 1;
	FearMax = 100;
	SpeedFear = 600;
	bIsInBerserkMode = false;
	TraceShape=FCollisionShape::MakeSphere(10.0f);
	DMGTorch = 1;

	

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

	GhostLight = CreateDefaultSubobject<USpotLightComponent>("GhostLight");
	GhostLight->SetupAttachment(RootComponent);


	//Setup OtherComponents
}

void ARoselia::BeginPlay()
{
	Super::BeginPlay();


	MyWorld = GetWorld();

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

void ARoselia::DOT()
{
	TraceShape.SetSphere(10.0f);
	float RadiusMultiplier = 1;
	float OffsetMultiplier = 15;
	FVector SphereOffset=TorchLight->GetForwardVector();
	for (int i = 0; i < 5; i++)
	{
		TArray<FHitResult> OutHits;
		TraceShape.SetSphere(TraceShape.GetSphereRadius() * RadiusMultiplier);
		MyWorld->SweepMultiByChannel(OutHits, TorchLight->GetComponentLocation()+SphereOffset*OffsetMultiplier, TorchLight->GetComponentLocation()+SphereOffset * OffsetMultiplier,FQuat::Identity, ECollisionChannel::ECC_Visibility, TraceShape);
		for (FHitResult Hits : OutHits)
		{
			FString x = Hits.Actor->StaticClass()->GetName();
			if (Cast<AEnemySimple_CPP>(Hits.GetActor()))
			{
				
				Cast<AEnemySimple_CPP>(Hits.GetActor())->LightManagement(DMGTorch);
			}
		}
		RadiusMultiplier *= 1.25f;
		OffsetMultiplier *=	2.5f;
		
	}
	TraceShape.SetSphere(10.0f);
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
		if (Fear > 0.1f) 
		{
			
			Fear -= 2.0f;
		}
		else
		{
			/*bIsInBerserkMode = false;
			GetCharacterMovement()->MaxWalkSpeed = 600;
			GhostLight->SetIntensity(.0f);
			MyWorld->GetTimerManager().ClearTimer(GhostLightDOT_TH);*/


			EndgameFunction(1);
		}

	}
}

void ARoselia::BerserkMode()
{
	bIsLightOn = true;
	LightSwitch();
	bIsInBerserkMode = true;
	FearDelegate.Broadcast();
	GetCharacterMovement()->MaxWalkSpeed = 1000;
	GhostLight->SetIntensity(100000.0f);
	MyWorld->GetTimerManager().SetTimer(GhostLightDOT_TH,this, &ARoselia::GHostLightDOT, 0.1f, true, 0.1f);

}

void ARoselia::GHostLightDOT()
{
	TraceShape.SetSphere(300.0f);
	TArray<FHitResult> OutHits;
	TraceShape.SetSphere(TraceShape.GetSphereRadius());
	MyWorld->SweepMultiByChannel(OutHits, TorchLight->GetComponentLocation(), TorchLight->GetComponentLocation(), FQuat::Identity, ECollisionChannel::ECC_Visibility, TraceShape);
	for (FHitResult Hits : OutHits)
	{			
		if (Cast<AEnemySimple_CPP>(Hits.GetActor()))
		{
			Cast<AEnemySimple_CPP>(Hits.GetActor())->LightManagement(DMGTorch);
		}
	}
}

void ARoselia::LightSwitch()
{
	if (!bIsInBerserkMode)
	{
		if (bIsLightOn)
		{
			bIsLightOn = false;
			TorchLight->SetIntensity(0);
			MyWorld->GetTimerManager().ClearTimer(DOT_TH);

		}

		else
		{
			bIsLightOn = true;
			TorchLight->SetIntensity(100000.f);
			MyWorld->GetTimerManager().SetTimer(DOT_TH, this, &ARoselia::DOT, 0.1f, true, .0f);
		}
	}

}

void ARoselia::CombatStart()
{
	
	MyWorld->GetTimerManager().SetTimer(FearManagement_TH, this, &ARoselia::FearManagement, 0.1f, true);
}

void ARoselia::CombatEnd()
{
	MyWorld->GetTimerManager().ClearTimer(FearManagement_TH);
	Fear = 0;
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

void ARoselia::SlowFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Kek"));
	if (!bIsSlowed)
	{
		bIsSlowed = true;
		GetCharacterMovement()->MaxWalkSpeed /= 2;
		MyWorld->GetTimerManager().SetTimer(StunManagement_TH, this, &ARoselia::StunManagement, 3);
	}
	else if (!bIsStunned) 
	{
		bIsStunned = true;
		GetCharacterMovement()->MaxWalkSpeed = 0;
		MyWorld->GetTimerManager().SetTimer(StunManagement_TH, this, &ARoselia::StunManagement, 1.5);
	}
	else
	{	
		SetLifeSpan(0.1f);
	}
}

void ARoselia::StunManagement()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
	bIsSlowed = false;
	bIsStunned = false;
	MyWorld->GetTimerManager().ClearTimer(StunManagement_TH);
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



