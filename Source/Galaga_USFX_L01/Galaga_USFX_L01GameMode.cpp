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
		// Asegúrate de crear y asignar EnemyCollection antes de intentar agregar enemigos
		EnemyCollection = World->SpawnActor<AEnemyCollection>();

		for (int i = 0; i < 5; i++) {
			FVector PosicionNaveActual = FVector(ubicacionInicioNavesEnemigasCaza.X, ubicacionInicioNavesEnemigasCaza.Y + i * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaCaza* NaveEnemigaCazaTemporal = World->SpawnActor<ANaveEnemigaCaza>(PosicionNaveActual, rotacionNave);

			TANavesEnemigas.Push(NaveEnemigaCazaTemporal);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Agregando nave enemiga caza a la colección: %d"),NaveIndex));
			EnemyCollection->AddEnemy(NaveEnemigaCazaTemporal);
			NaveIndex++;

		}

		float nuevaposicionX = ubicacionInicioNavesEnemigasTransporte.X - 300.0f;

		for (int j = 0; j < 5; j++) {
			FVector PosicionNaveActual = FVector(nuevaposicionX, ubicacionInicioNavesEnemigasCazaAlfa.Y + j * 300, ubicacionInicioNavesEnemigasCazaAlfa.Z);
			ANaveEnemigaTransporte* NaveEnemigaTransporteTemporal = World->SpawnActor<ANaveEnemigaTransporte>(PosicionNaveActual, rotacionNave);

			TANavesEnemigas.Push(NaveEnemigaTransporteTemporal);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Agregando nave enemiga transporte a la colección: %d"), NaveIndex));
			EnemyCollection->AddEnemy(NaveEnemigaTransporteTemporal);
			NaveIndex++;

		}

		float nuevaposicionX2 = ubicacionInicioNavesEnemigasCazaAlfa.X - 600.0f;
		// Crear el iterador después de haber agregado todos los enemigos a la colección
		
	//}
		for (int x = 0; x < 5; x++) {
			FVector PosicionNaveActual = FVector(nuevaposicionX2, ubicacionInicioNavesEnemigasTransporte.Y + x * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaCazaAlfa* NaveEnemigaCazaAlfaTemporal = World->SpawnActor<ANaveEnemigaCazaAlfa>(PosicionNaveActual, rotacionNave);

			//TANavesEnemigasCaza.Push(NaveEnemigaCazaTemporal);
			TANavesEnemigas.Push(NaveEnemigaCazaAlfaTemporal);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Agregando nave enemiga caza alfa a la colección: %d"),NaveIndex));
			EnemyCollection->AddEnemy(NaveEnemigaCazaAlfaTemporal);
			NaveIndex++;

		}
		EnemyIterator = EnemyCollection->CreateIterator();

		//const int32 NumeroDeColumnasCaza = 2;
		//const int32 NumeroDeFilasCaza = 5;

		//for (int32 Columna = 0; Columna < NumeroDeColumnasCaza; ++Columna)
		//{
		//	TArray<ANaveEnemigaCaza*> NavesEnColumna;
		//	for (int32 Fila = 0; Fila < NumeroDeFilasCaza; ++Fila)
		//	{
		//		FVector SpawningLocation = FVector(Columna * 300 + 300.0f, Fila * 200 + -500.0f, 250.0f);
		//		FRotator SpawningRotation = FRotator::ZeroRotator;

		//		ANaveEnemigaCaza* NuevaNaveCaza = GetWorld()->SpawnActor<ANaveEnemigaCaza>(SpawningLocation, SpawningRotation);
		//		NavesEnColumna.Add(NuevaNaveCaza);
		//		
		//	}
		//	ColumnaNavesEnemigasCaza.Add(Columna, NavesEnColumna);
		//}

		////NaveEnemigaTransporte01 = World->SpawnActor<ANaveEnemigaTransporte>(ubicacionNave01, rotacionNave);
		////NaveEnemigaCaza01 = World->SpawnActor<ANaveEnemigaCaza>(ubicacionNave02, rotacionNave);

		//TiempoTranscurrido = 0;


	
	}

	

}

void AGalaga_USFX_L01GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TiempoTranscurrido++;

	// Asegúrate de que el iterador y la colección de enemigos han sido inicializados
	if (EnemyIterator && EnemyCollection)
	{
		//if (EnemyCollection)
		//{
			IIteradorInterface* Iterator = EnemyCollection->CreateIterator();
			while (Iterator->HasNext())
			{
				AActor* EnemyActor = Iterator->Next();
				ANaveEnemigaCaza* EnemyShip = Cast<ANaveEnemigaCaza>(EnemyActor);
				ANaveEnemigaCazaAlfa* EnemyShip2 = Cast<ANaveEnemigaCazaAlfa>(EnemyActor);
				if (EnemyShip)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moviendo y Disparando Nave Enemiga Caza: %s"));
					EnemyShip->Mover(DeltaTime);
					EnemyShip->Disparar();
					//EnemyShip2->Mover(DeltaTime);
				}
				if (EnemyShip2)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moviendo y Disparando Nave Enemiga Caza Alfa: %s"));
					EnemyShip2->Mover(DeltaTime);
					//EnemyShip2->Disparar();
				}
			}
			// Asegúrate de limpiar el iterador si es necesario
		//}
	}

	
}
