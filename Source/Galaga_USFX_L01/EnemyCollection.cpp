// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCollection.h"
#include "NaveEnemiga.h"
#include "EnemyIterator.h"
// Sets default values
AEnemyCollection::AEnemyCollection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCollection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

IIteradorInterface* AEnemyCollection::CreateIterator() const
{
    AEnemyIterator* Iterator = GetWorld()->SpawnActor<AEnemyIterator>();
    if (Iterator)
    {
        Iterator->SetEnemyCollection(const_cast<AEnemyCollection*>(this)); // const_cast es usado para remover la constante de un objeto
        return Iterator;
    }
    return nullptr;
}

void AEnemyCollection::AddEnemy(class AActor* Enemy)
{
    if (Enemy)
    {
        EnemyShips.Add(Enemy);
    }

	
}

