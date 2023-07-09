// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeCPP.h"

// Sets default values
ANodeCPP::ANodeCPP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(defaultSceneRoot);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nodo"));
	cube->AttachToComponent(defaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ANodeCPP::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANodeCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
