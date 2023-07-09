// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPathfinderCPP.h"


TArray<FVector> UAStarPathfinderCPP::computeAStar(const FVector& initPos, const FVector& goal)
{
	openList->clear();	// Primero se limpia la cola con prioridad
	TMap<ANodeCPP*, ANodeCPP*> cameFrom;
	TMap< ANodeCPP*, float> gScore;

	// Obtención de las referencias a los nodos
	FGridCoordinate aux = grid->getGridPosition(initPos);
	ANodeCPP* initPosNode = grid->getNode(aux);

	aux = grid->getGridPosition(goal);
	ANodeCPP* goalNode = grid->getNode(aux);


	openList->put(FQueueElementCPP(*initPosNode, 0));	// Se inserta en la lista de abiertos

	cameFrom.Add(initPosNode, nullptr);
	gScore.Add(initPosNode, 0);

	bool finished = false;

	while (!finished) {
		ANodeCPP* current = openList->pop().node;

		if (current == goalNode)
			finished = true;

		else {
			for (ANodeCPP* neighbor : current->neighbors) {
				float newCostG = *gScore.Find(current) + nodeCost(*neighbor);

				if (!gScore.Contains(neighbor) || (newCostG < *gScore.Find(neighbor))) {
					gScore.Add(neighbor, newCostG);
					float costF = newCostG + heuristic(neighbor->cube->GetComponentLocation(), goal);
					openList->put(FQueueElementCPP(*neighbor, costF));
					cameFrom.Add(neighbor, current);
				}
			}

			finished = openList->empty();
		}
	}

	return reconstructPath(cameFrom, *goalNode, *initPosNode);
}

float UAStarPathfinderCPP::heuristic(const FVector& A, const FVector& goal)
{
	//Distancia Manhattan
	return FMath::Abs(A.X - goal.X) + FMath::Abs(A.Y - goal.Y);

	/*
	// Distancia Chebyshev
	float dx = FMath::Abs(A.X - goal.X);
	float dy= FMath::Abs(A.Y - goal.Y);
	const float D = 1.0, D2 = 1.0;

	return D * (dx + dy) + (D2 - 2 * D) * FMath::Min(dx, dy);
	*/
}

float UAStarPathfinderCPP::nodeCost(const ANodeCPP& nextNode)
{
	float res = 200;

	if (nextNode.isDelimiter)
		res = 900000;

	else if (nextNode.hasObstacle)
		res = 2000;

	else if (nextNode.isOptimal)
		res = 0.1;

	return res;
}

TArray<FVector> UAStarPathfinderCPP::reconstructPath(TMap<ANodeCPP*, ANodeCPP*>& cameFrom, ANodeCPP& goal, const ANodeCPP& start)
{
	ANodeCPP* current = &goal;
	TArray<FVector> path;

	if (!cameFrom.Contains(current)) {
		return path;
	}

	while (current != &start) {
		path.Add(current->cube->GetComponentLocation());
		current = *cameFrom.Find(current);
	}

	path.Add(start.cube->GetComponentLocation());
	Algo::Reverse(path);

	return path;
}
