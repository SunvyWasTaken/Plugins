// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExedrePortal.generated.h"

UCLASS()
class SUNLIBRARY_API AExedrePortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExedrePortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Statut du portal (Soit actif ou pas) pour éviter de trop drop les FPS.
	UFUNCTION(BlueprintPure, Category = "Exedre|Portal")
		bool IsActive();

	// Permet d'activé depuis un BP
	UFUNCTION(BlueprintCallable, Category = "Exedre|Portal")
		void SetActive(bool NewActive);

	//Render target to use to display the portal
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Exedre|Portal")
		void ClearRTT();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Exedre|Portal")
		void SetRTT(UTexture* RenderTexture);

	UFUNCTION(BlueprintNativeEvent, Category = "Exedre|Portal")
		void ForceTick();

	//Target of where the portal is looking
	UFUNCTION(BlueprintPure, Category = "Exedre|Portal")
		AActor* GetTarget();

	UFUNCTION(BlueprintCallable, Category = "Exedre|Portal")
		void SetTarget(AActor* NewTarget);

	//Helpers
	UFUNCTION(BlueprintCallable, Category = "Exedre|Portal")
		bool IsPointInFrontOfPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

	UFUNCTION(BlueprintCallable, Category = "Exedre|Portal")
		bool IsPointCrossingPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

	UFUNCTION(BlueprintCallable, Category = "Exedre|Portal")
		void TeleportActor(AActor* ActorToTeleport);

protected:
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* PortalRootComponent;

private:
	bool bIsActive;

	AActor* Target;

	//Used for Tracking movement of a point
	FVector LastPosition;
	bool    LastInFront;

};
