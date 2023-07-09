// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeCPP.generated.h"


/**
* Actor que representa un nodo en la malla de navegación.
*/
UCLASS()
class RACINGAI_API ANodeCPP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANodeCPP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* cube;

	UPROPERTY(EditAnywhere)
		USceneComponent* defaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isOptimal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDelimiter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isCheckpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ANodeCPP*> neighbors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
