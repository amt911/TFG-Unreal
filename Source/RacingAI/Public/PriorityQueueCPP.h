// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PriorityQueueCPP.generated.h"


class ANodeCPP;


/**
* Representa un elemento de la cola con prioridad.
*/
USTRUCT()
struct FQueueElementCPP {
	GENERATED_BODY()

	UPROPERTY()
	ANodeCPP* node;

	UPROPERTY()
	float cost;

	FQueueElementCPP() : node(nullptr), cost(-1) {}
	FQueueElementCPP(ANodeCPP& node, float cost) : node(&node), cost(cost) {};

	/**
	* Sobrecarga del operador <, para poder ser ordenado en estructuras de datos.
	* 
	* @param other Elemento con el que se desea comparar.
	* 
	* @return Valor que indica si el objeto que ha llamado al m�todo es menor que other.
	*/
	bool operator<(const FQueueElementCPP& other) const;
};

/**
 * Representa una cola con prioridad, utilizada para el algoritmo de navegaci�n.
 */
UCLASS()
class RACINGAI_API UPriorityQueueCPP : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FQueueElementCPP> queue;


	/**
	* A�ade el elemento pasado como p�rametro a la cola.
	* 
	* @param element Elemento que se desea a�adir.
	*/
	void put(const FQueueElementCPP& element);

	/**
	* Elimina el elemento del final de la cola.
	* 
	* @return El elemento eliminado.
	*/
	FQueueElementCPP pop();

	/**
	* Comprueba si la cola est� vac�a.
	* 
	* @return Verdadero si est� vac�a y falso en otro caso.
	*/
	bool empty() const;

	/**
	* Limpia la cola con prioridad.
	*/
	void clear();
};
