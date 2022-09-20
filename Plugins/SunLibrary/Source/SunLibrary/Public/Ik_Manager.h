// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ik_Manager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUNLIBRARY_API UIk_Manager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIk_Manager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, meta =(DisplayName = "Bone Name Left"), Category = "Parameters")
	FName BoneNameLeft;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Bone Name Right"), Category = "Parameters")
	FName BoneNameRight;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Trace Distance Below Capsule"), Category = "Parameters")
		float TraceDistanceBelowCapsule { 100 };

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Interp Speed"), Category = "Parameters")
		float InterpSpeed{ 50 };

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Left Offset"), Category = "Offset")
	float GetLeftOffset();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Right Offset"), Category = "Offset")
	float GetRightOffset();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Pelvis Offset"), Category = "Offset")
	float GetPelvisOffset();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Left Rotation"), Category = "Offset")
	FRotator GetLeftRotation();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Right Rotation"), Category = "Offset")
	FRotator GetRightRotation();

protected:

	UPROPERTY()
		ACharacter* PlayerRef;

	UPROPERTY()
	float LeftFootOffset;

	UPROPERTY()
	float RightFootOffset;

	UPROPERTY()
	float PelvisOffset;

	UPROPERTY()
	FRotator LeftFootRotation;

	UPROPERTY()
	FRotator RightFootRotation;

	//Trace a line trace from the pelvis to the bottom of the foot so u can know the offset between the floor and the foot
	UFUNCTION(Category = "Offset")
	void F_TraceFromFoot(FName BoneName, float TraceBelowCapsule, float &Offset, FVector &ImpactNormal);

	UFUNCTION(Category = "Offset")
	FRotator F_CalculateRotationOffset(FRotator CurrentRotation, FVector FloorNormal, float DeltaSeconds);
		
};
