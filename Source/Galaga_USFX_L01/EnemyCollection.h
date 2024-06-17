// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectionInterface.h"
#include "EnemyCollection.generated.h"

UCLASS()
class GALAGA_USFX_L01_API AEnemyCollection : public AActor, public ICollectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyCollection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
		virtual IIteradorInterface* CreateIterator() const override;
		void AddEnemy(class AActor* Enemy);
public:
		TArray<class AActor*> EnemyShips;


};
