// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGridCPP.h"

// Sets default values
AAStarGridCPP::AAStarGridCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void AAStarGridCPP::BeginPlay()
{
	Super::BeginPlay();
	
	spawnGrid();
	setNeighbors();
}


void AAStarGridCPP::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	destroyNodes();
}


// Called every frame
void AAStarGridCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAStarGridCPP::spawnGrid()
{
	for (int i = 0; i < GRID_SIZE; i++) {
		FVector lastPosition = FVector(startingPosition.X, ((i * NODE_SIZE) + startingPosition.Y), 0.0);

		for (int j = 0; j < GRID_SIZE; j++) {
			FActorSpawnParameters parametros = FActorSpawnParameters();
			parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ANodeCPP* newActor = GetWorld()->SpawnActor<ANodeCPP>(nodeClass, FTransform(FRotator(0), lastPosition, FVector((NODE_SIZE / 100.0), (NODE_SIZE / 100.0), 1)), parametros);

			nodes.Add(newActor);

			lastPosition.X += NODE_SIZE;
		}
	}
}


void AAStarGridCPP::setNeighbors()
{
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			ANodeCPP* nodo = getNode(FGridCoordinate(i, j));

			// Arriba
			if (i > 0) {
				getNode(FGridCoordinate(i - 1, j))->neighbors.Add(nodo);
			}

			// Abajo
			if ((i + 1) < GRID_SIZE) {
				getNode(FGridCoordinate(i + 1, j))->neighbors.Add(nodo);
			}

			// Izquierda
			if (j > 0) {
				getNode(FGridCoordinate(i, j - 1))->neighbors.Add(nodo);
			}

			// Derecha
			if ((j + 1) < GRID_SIZE) {
				getNode(FGridCoordinate(i, j + 1))->neighbors.Add(nodo);
			}
		}
	}
}


FGridCoordinate AAStarGridCPP::getGridPosition(const FVector& worldLocation)
{
	FVector adjustedVector = FVector(getNearestValue(true, worldLocation.X), getNearestValue(false, worldLocation.Y), 0.0);

	float xComp = adjustedVector.X;
	adjustedVector.X = (adjustedVector.Y - startingPosition.Y) / (NODE_SIZE * 1.0);
	adjustedVector.Y = (xComp - startingPosition.X) / (NODE_SIZE * 1.0);

	return FGridCoordinate(adjustedVector.X, adjustedVector.Y);
}


ANodeCPP* AAStarGridCPP::getNode(const FGridCoordinate& gridPosition)
{
	FGridCoordinate res(checkGridLimits(gridPosition.fil), checkGridLimits(gridPosition.col));

	return nodes.GetData()[getArrayPosition(res)];
}


int AAStarGridCPP::getArrayPosition(const FGridCoordinate& gridPosition)
{
	return (checkGridLimits(gridPosition.fil) * GRID_SIZE) + checkGridLimits(gridPosition.col);
}


float AAStarGridCPP::getNearestValue(const bool isX, const float value)
{
	float lowerValue = 0.0, finalVal = 0.0;
	float higherValue = (isX) ? startingPosition.X : startingPosition.Y;
	higherValue -= NODE_SIZE;

	if ((value >= (higherValue + NODE_SIZE)) && (value <= (higherValue + NODE_SIZE + (GRID_SIZE * NODE_SIZE)))) {
		bool finished = false;

		while (!finished) {
			higherValue += NODE_SIZE;

			if (higherValue > value) {
				finished = true;
				lowerValue = higherValue - NODE_SIZE;
			}

			finalVal = ((higherValue - value) < (value - lowerValue)) ? higherValue : lowerValue;
		}
	}

	else {
		finalVal = (value < (higherValue + NODE_SIZE)) ? (higherValue + NODE_SIZE) : (higherValue + NODE_SIZE + (GRID_SIZE * NODE_SIZE));
	}

	return finalVal;
}


FVector AAStarGridCPP::getWorldLocation(const FGridCoordinate& gridPosition)
{
	return FVector(((checkGridLimits(gridPosition.fil) * NODE_SIZE) + startingPosition.X), ((checkGridLimits(gridPosition.col) * NODE_SIZE) + startingPosition.Y), 0.0);
}


int AAStarGridCPP::checkGridLimits(const int value)
{
	int res = value;

	if (value < 0) {
		res = value;
	}
	else if (value >= GRID_SIZE) {
		res = GRID_SIZE - 1;
	}

	return res;
}


void AAStarGridCPP::destroyNodes()
{
	auto ptr = nodes.GetData();

	for (int i = 0; i < nodes.Num(); i++) {
		ptr[i]->Destroy();
	}
}
