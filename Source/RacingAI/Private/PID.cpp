// Fill out your copyright notice in the Description page of Project Settings.


#include "PID.h"

UPID::UPID()
{
	Kp = Kd = Ki = errorAcumulado = errorAcumulado = 0.0;
}

UPID::UPID(float Kp, float Ki, float Kd) : Kp(Kp), Ki(Ki), Kd(Kd)
{
	errorAcumulado = errorPasado = 0.0;
}

float UPID::updatePID(float deltaSeconds, float errorActual)
{
	float result = 0.0;

	errorAcumulado = (deltaSeconds * errorActual) + errorAcumulado;

	float derivativo = (errorActual - errorPasado) / deltaSeconds;

	result = (Kp * errorActual) + (Ki * errorAcumulado) + (Kd * derivativo);

	errorPasado = errorActual;

	return result;
}
