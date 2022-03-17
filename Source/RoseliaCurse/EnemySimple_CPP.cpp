#include "EnemySimple_CPP.h"
#include "EnemySimple_CPP.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Roselia.h"


AEnemySimple_CPP::AEnemySimple_CPP() 
{
	HPMax = 2;
	HPActual = HPMax;
	bCanTakeDMG = true;
}

void AEnemySimple_CPP::BeginPlay()
{
	Super::BeginPlay();
	//(Cast<ARoselia>(UGameplayStatics::GetActorOfClass(GetWorld(), ARoselia::StaticClass())))->FearDelegate.Add(&AEnemySimple_CPP::FearSwitch);
	
}

void AEnemySimple_CPP::HPManagement(float DMG)
{
	if (bCanTakeDMG == true)
	{
		if (HPActual > DMG)
		{
			HPActual -= DMG;
			bCanTakeDMG = false;
			GetWorld()->GetTimerManager().SetTimer(DMGReset_TH, this, &AEnemySimple_CPP::DMGReset, 1.0f, false);
		}
		else
			SetLifeSpan(0.1f);
	}


}

void AEnemySimple_CPP::DMGReset()
{
	bCanTakeDMG = true;
}

void AEnemySimple_CPP::LightManagement(float DMG)
{
	
	HPManagement(DMG);
	//GetWorld()->GetTimerManager().SetTimer(FearSwitch_TH,this,&AEnemySimple_CPP::FearSwitch, 2, true,.0f);
	FearSwitch();
}

void AEnemySimple_CPP::FearSwitch_Implementation()
{
}

