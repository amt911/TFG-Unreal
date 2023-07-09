// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NodeCPP.h>
#include "AStarGridCPP.generated.h"


/**
* Estrctura que representa las coordenadas de una matriz.
*/
USTRUCT(BlueprintType)
struct FGridCoordinate {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fil;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int col;

	FGridCoordinate() : fil(0), col(0) {}
	FGridCoordinate(int fil, int col) : fil(fil), col(col) {}
};


/**
* Clase que representa la malla de navegación utilizada para generar rutas.
*/
UCLASS(BlueprintType)
class RACINGAI_API AAStarGridCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarGridCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TSubclassOf<ANodeCPP> nodeClass;		// Para obtener la clase del nodo

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ANodeCPP*> nodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GRID_SIZE = 250;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NODE_SIZE = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector startingPosition = FVector(-12600, -12600, 0);

private:
	/**
	* Crea la malla de navegación.
	*/
	void spawnGrid();

	/**
	* Añade a los nodos de la malla una referencia a sus vecinos.
	*/
	void setNeighbors();

	/**
	* Obtiene el índice del array de nodos a partir de la posción en la matriz.
	* 
	* @param gridPosition Posición del nodo en la matriz (filas y columnas).
	* 
	* @return Posición del nodo en el array.
	*/
	int getArrayPosition(const FGridCoordinate& gridPosition);

	/**
	* Ajusta el valor a las coordenadas del mundo más cercanas.
	* 
	* @param isX Indica si se debe hacer en la coordenada X del mundo.
	* 
	* @return Coordenadas del mundo ajustadas.
	*/
	float getNearestValue(const bool isX, const float value);

	/**
	* Obtiene las coordenadas del mundo a partir de las coordenadas en la matriz.
	* 
	* @param gridPosition Posición en la matriz de nodos.
	* 
	* @return Vector con la posición en coordenadas del mundo.
	*/
	FVector getWorldLocation(const FGridCoordinate& gridPosition);

	/**
	* Ajusta el valor para que se encuentr dentro de los límites de la matriz.
	* 
	* @param value Valor que se quiere ajustar.
	* 
	* @return Valor ajustado, en caso de estar fuera de los límites de la matriz.
	* Valor sin modificar en otro caso.
	* 
	* @note Se pueden insertar tanto las coordenadas de filas como de columnas, ya que la malla
	* es cuadrada.
	*/
	int checkGridLimits(const int value);	

	/**
	* Destruye los nodos de la malla de navegación al acabar la partida.
	*/
	void destroyNodes();

public:

	/**
	* Obtiene la posición en la matriz a partir de las coordenadas del mundo.
	* 
	* @param worldLocation Coordenadas del mundo que se desean convertir.
	* 
	* @return Coordenadas de la matriz.
	* 
	* @note Las coordenadas del mundo pueden no ser exactas, e incluso estar fuera de la propia matriz,
	* ya que se ajustará su valor.
	*/
	UFUNCTION(BlueprintCallable)
	FGridCoordinate getGridPosition(const FVector& worldLocation);
	

	/**
	* Obtiene una referencia al nodo que se encuentra en la posición de la matriz especificada en 
	* la entrada.
	* 
	* @param gridPosition Posición en la matriz (filas y columnas).
	* 
	* @return Referencia al nodo que se encuentra en la posición especificada.
	* 
	* @note Las coordenadas pueden estar fuera de rango, ya que son ajustadas.
	*/
	UFUNCTION(BlueprintCallable)
	ANodeCPP *getNode(const FGridCoordinate& gridPosition);
};
