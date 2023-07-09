// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <AStarGridCPP.h>
#include <PriorityQueueCPP.h>
#include "AStarPathfinderCPP.generated.h"

/**
 * Clase encargada de implementar el algoritmo de navegación para el cálculo de rutas.
 */
UCLASS(BlueprintType)
class RACINGAI_API UAStarPathfinderCPP : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	AAStarGridCPP* grid;
	
	/**
	* Genera una ruta utilizando el algoritmo A*.
	* 
	* @param iniPos Posición inicial desde donde se quiere generar la ruta. En coordenadas del mundo.
	* @param goal Posición final a la que se quiere llegar. En coordenadas del mundo.
	* 
	* @return Vector de coordenadas del mundo con la ruta generada.
	*/
	UFUNCTION(BlueprintCallable)
	TArray<FVector> computeAStar(const FVector& initPos, const FVector& goal);

private:
	UPROPERTY()
	UPriorityQueueCPP* openList = NewObject<UPriorityQueueCPP>();


	/**
	* Calcula el coste de ir desde un punto hasta el destino. Utilizando la distancia Manhattan.
	* 
	* @param A Posición en coordenadas del mundo desde donde se quiere calcular.
	* @param goal Posición de destino en coordenadas del mundo.
	* 
	* @return Coste calculado entre los dos puntos.
	*/
	float heuristic(const FVector& A, const FVector& goal);

	/**
	* Calcula el coste de pasar al siguiente nodo.
	* 
	* @param nextNode Nodo siguiente al que se quiere pasar.
	* 
	* @return Coste de pasar a nextNode.
	*/
	float nodeCost(const ANodeCPP& nextNode);

	/**
	* Genera el camino obtenido por A* para que sea utilizable por otras entidades.
	* 
	* @param cameFrom Estructura que almacena de que nodo ha venido para llegar al otro.
	* @param goal Nodo destino.
	* @param start Nodo de inicio.
	* 
	* @return Vector con las posiciones en coordenadas del mundo y la ruta generada.
	*/
	TArray<FVector> reconstructPath(TMap<ANodeCPP*, ANodeCPP*>& cameFrom, ANodeCPP& goal, const ANodeCPP& start);
};
