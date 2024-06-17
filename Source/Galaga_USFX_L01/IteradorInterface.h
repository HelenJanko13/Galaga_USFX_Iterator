// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IteradorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIteradorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GALAGA_USFX_L01_API IIteradorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Método para obtener la nave actual del iterador
	//virtual class AActor* GetCurrentShip() const = 0;
	virtual class AActor* Next() = 0;
	virtual bool HasNext() = 0;
};
