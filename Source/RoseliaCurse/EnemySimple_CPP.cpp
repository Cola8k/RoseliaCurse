// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySimple_CPP.h"
#include "TimerManager.h"


AEnemySimple_CPP::AEnemySimple_CPP() 
{
	HPMax = 2;
	HPActual = HPMax;
}

void AEnemySimple_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySimple_CPP::HPManagement(float DMG)
{
	if (HPActual > DMG)
		HPActual-=DMG;
	else
		SetLifeSpan(0.1f);
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

