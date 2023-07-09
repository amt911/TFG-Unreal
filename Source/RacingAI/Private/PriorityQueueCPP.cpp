// Fill out your copyright notice in the Description page of Project Settings.


#include "PriorityQueueCPP.h"

void UPriorityQueueCPP::put(const FQueueElementCPP& element)
{
	queue.HeapPush(element);
}

FQueueElementCPP UPriorityQueueCPP::pop()
{
	FQueueElementCPP aux;

	queue.HeapPop(aux);

	return aux;
}

bool UPriorityQueueCPP::empty() const
{
	return queue.IsEmpty();
}

void UPriorityQueueCPP::clear()
{
	queue.Empty();
}

bool FQueueElementCPP::operator<(const FQueueElementCPP& other) const
{
	return this->cost < other.cost;
}
