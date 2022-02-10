// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPosition_CPP.h"
#include "Components/SceneComponent.h"

// Sets default values
ACameraPosition_CPP::ACameraPosition_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraPos = CreateDefaultSubobject<USceneComponent>("CameraPos");
	RootComponent = CameraPos;
}

