// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L01GameMode.h"
#include "Galaga_USFX_L01Pawn.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaTransporte.h"
#include "NaveEnemigaCaza.h"
#include "NaveEnemigaCazaAlfa.h"

#include "EnemyCollection.h"
#include "EnemyIterator.h"
#include "IteradorInterface.h"

AGalaga_USFX_L01GameMode::AGalaga_USFX_L01GameMode()
{
	// set default pawn class to our character class
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = AGalaga_USFX_L01Pawn::StaticClass();

	//NaveEnemiga01 = nullptr;
}

void AGalaga_USFX_L01GameMode::BeginPlay()
{
	Super::BeginPlay();
	//Set the game state to playing
	FVector ubicacionInicioNavesEnemigasCaza = FVector(-300.0f, 500.0f, 250.0f);
	FVector ubicacionInicioNavesEnemigasTransporte = FVector(500.0f, 500.0f, 250.0f);
	FVector ubicacionInicioNavesEnemigasCazaAlfa = FVector(600.0f, 500.0f, 250.0f);

	//FVector ubicacionNave01 = FVector(-1000.0f, 500.0f, 250.0f);
	//FVector ubicacionNave02 = FVector(-500.0f, -500.0f, 250.0f);



	FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Aseg�rate de crear y asignar EnemyCollection antes de intentar agregar enemigos
		EnemyCollection = World->SpawnActor<AEnemyCollection>();

		for (int i = 0; i < 5; i++) {
			FVector PosicionNaveActual = FVector(ubicacionInicioNavesEnemigasCaza.X, ubicacionInicioNavesEnemigasCaza.Y + i * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaCaza* NaveEnemigaCazaTemporal = World->SpawnActor<ANaveEnemigaCaza>(PosicionNaveActual, rotacionNave);

			TANavesEnemigas.Push(NaveEnemigaCazaTemporal);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Agregando nave enemiga caza a la coleccion: %d"),NaveIndex));
			EnemyCollection->AddEnemy(NaveEnemigaCazaTemporal);
			NaveIndex++;

		}

		float nuevaposicionX = ubicacionInicioNavesEnemigasTransporte.X - 300.0f;

		for (int j = 0; j < 5; j++) {
			FVector PosicionNaveActual = FVector(nuevaposicionX, ubicacionInicioNavesEnemigasCazaAlfa.Y + j * 300, ubicacionInicioNavesEnemigasCazaAlfa.Z);
			ANaveEnemigaTransporte* NaveEnemigaTransporteTemporal = World->SpawnActor<ANaveEnemigaTransporte>(PosicionNaveActual, rotacionNave);

			TANavesEnemigas.Push(NaveEnemigaTransporteTemporal);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Agregando nave enemiga transporte a la coleccion: %d"), NaveIndex));
			EnemyCollection->AddEnemy(NaveEnemigaTransporteTemporal);
			NaveIndex++;

		}

		float nuevaposicionX2 = ubicacionInicioNavesEnemigasCazaAlfa.X - 600.0f;
		
		
	//}
		for (int x = 0; x < 5; x++) {
			FVector PosicionNaveActual = FVector(nuevaposicionX2, ubicacionInicioNavesEnemigasTransporte.Y + x * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaCazaAlfa* NaveEnemigaCazaAlfaTemporal = World->SpawnActor<ANaveEnemigaCazaAlfa>(PosicionNaveActual, rotacionNave);

			//TANavesEnemigasCaza.Push(NaveEnemigaCazaTemporal);
			TANavesEnemigas.Push(NaveEnemigaCazaAlfaTemporal);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Agregando nave enemiga caza alfa a la colecci�n: %d"),NaveIndex));
			EnemyCollection->AddEnemy(NaveEnemigaCazaAlfaTemporal);
			NaveIndex++;

		}
		// Crear el iterador despu�s de haber agregado todos los enemigos a la colecci�n
		EnemyIterator = EnemyCollection->CreateIterator();

		
	
	}

	

}

void AGalaga_USFX_L01GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TiempoTranscurrido++;

	
	if (EnemyIterator && EnemyCollection)
	{
		
		EnemyIterator->Reset();
			//IIteradorInterface* Iterator = EnemyCollection->CreateIterator();
			while (EnemyIterator->HasNext())
			{
				AActor* EnemyActor = EnemyIterator->Next();
				ANaveEnemigaCaza* EnemyShip = Cast<ANaveEnemigaCaza>(EnemyActor);
				ANaveEnemigaCazaAlfa* EnemyShip2 = Cast<ANaveEnemigaCazaAlfa>(EnemyActor);
				if (EnemyShip)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moviendo y Disparando Nave Enemiga Caza: %s"));
					EnemyShip->Mover(DeltaTime);
					EnemyShip->Disparar();
				}
				if (EnemyShip2)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moviendo y Disparando Nave Enemiga Caza Alfa: %s"));
					EnemyShip2->Mover(DeltaTime);
					//EnemyShip2->Disparar();
				}
			}
	}

	
}
