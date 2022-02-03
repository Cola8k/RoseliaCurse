// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPosition.h"
#include "UObject/ConstructorHelpers.h"



// Sets default values
ACameraPosition::ACameraPosition()
{
	Floor = CreateDefaultSubobject<UStaticMeshComponent>("Floor");
	ConstructorHelpers::FObjectFinder<UStaticMesh>FloorAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	CameraOffset = FVector(0, 0, 600);
	Floor->SetStaticMesh(FloorAsset.Object);
	Floor->SetRelativeScale3D(FVector(300, 300, 1));
}

// Called when the game starts or when spawned
void ACameraPosition::BeginPlay()
{
	Super::BeginPlay();

}



