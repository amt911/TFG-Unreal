// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PID.generated.h"

/**
 * Entidad que representa un controlador PID genérico para la estabilización de valores en sistemas.
 */
UCLASS(BlueprintType)
class RACINGAI_API UPID : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float Kp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float Ki;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float Kd;	//Constantes del controlador

private:
	float errorAcumulado, errorPasado;	//Errores utilizados por el controlador

public:
	UPID();
	UPID(float Kp, float Ki, float Kd);

	/**
	* Actualiza el valor del controlador PID.
	* 
	* @param deltaSeconds Fracción de segundos desde el instante anterior.
	* @param errorActual Error actual que hay al valor que se desea llegar.
	* 
	* @return Valor utilizable por el sistema para controlar los actuadores (o el volante en mi caso).
	*/
	UFUNCTION(BlueprintCallable)
	float updatePID(float deltaSeconds, float errorActual);

};