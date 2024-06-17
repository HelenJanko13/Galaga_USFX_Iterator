// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyIterator.h"
#include "EnemyCollection.h"

// Sets default values
AEnemyIterator::AEnemyIterator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	//EnemyShips=TArray<AActor*>();

}

// Called when the game starts or when spawned
void AEnemyIterator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyIterator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//AActor* AEnemyIterator::GetCurrentShip() const
//{ 
//	if (_EnemyCollection && _EnemyCollection->EnemyShips.IsValidIndex(EnemyIndex))
//	{
//		return _EnemyCollection->EnemyShips[EnemyIndex];
//	}
//	return nullptr;
//}
void AEnemyIterator::SetEnemyCollection(AEnemyCollection* EnemyCollection)
{
		_EnemyCollection= EnemyCollection;
		EnemyIndex = -1; // Inicializa el índice en -1 para que el primer elemento sea el 0
}
AActor* AEnemyIterator::Next()
{
	if (HasNext()) // Primero verifica si hay un siguiente elemento
	{
		++EnemyIndex; // Incrementa el índice para moverse al siguiente elemento
		// Realiza un cast dinámico de ANaveEnemiga* a AActor* antes de devolverlo
		return Cast<AActor>(_EnemyCollection->EnemyShips[EnemyIndex]); // Devuelve el elemento actual después de incrementar
	}
	return nullptr; // Si no hay siguiente elemento, devuelve nullptr
}

bool AEnemyIterator::HasNext()
{
	if (_EnemyCollection && _EnemyCollection->EnemyShips.IsValidIndex(EnemyIndex + 1))
	{
		return true; // Hay un siguiente elemento
	}
	return false; // No hay un siguiente elemento
}

