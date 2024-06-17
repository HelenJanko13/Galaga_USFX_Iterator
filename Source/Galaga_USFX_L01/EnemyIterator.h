// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IteradorInterface.h"
#include "EnemyIterator.generated.h"

UCLASS()
class GALAGA_USFX_L01_API AEnemyIterator : public AActor, public IIteradorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyIterator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// Método para obtener la nave actual del iterador
	//virtual class AActor* GetCurrentShip() const override;
	void SetEnemyCollection(class AEnemyCollection* EnemyCollection);

	virtual class AActor* Next() override;
	virtual bool HasNext() override;
	virtual void Reset() override { EnemyIndex = -1; }
	private:

		class AEnemyCollection* _EnemyCollection;
		int32 EnemyIndex;
};
