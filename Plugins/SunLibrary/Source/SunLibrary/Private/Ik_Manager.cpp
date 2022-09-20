// Fill out your copyright notice in the Description page of Project Settings.


#include "Ik_Manager.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SunLibrary/Public/SunLibraryBPLibrary.h"

// Sets default values for this component's properties
UIk_Manager::UIk_Manager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIk_Manager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//Get le Owner pour pouvoir avoir directement la ref du skeletal mesh
	PlayerRef = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UIk_Manager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LeftFloorNormal;
	float LeftTarget;
	F_TraceFromFoot(BoneNameLeft, TraceDistanceBelowCapsule, LeftTarget, LeftFloorNormal);
	LeftFootOffset = UKismetMathLibrary::FInterpTo_Constant(LeftFootOffset, LeftTarget, DeltaTime, InterpSpeed);

	FVector RightFloorNormal;
	float RightTarget;
	F_TraceFromFoot(BoneNameRight, TraceDistanceBelowCapsule, RightTarget, LeftFloorNormal);
	RightFootOffset = UKismetMathLibrary::FInterpTo_Constant(RightTarget, RightTarget, DeltaTime, InterpSpeed);

	PelvisOffset = UKismetMathLibrary::FInterpTo_Constant(PelvisOffset, UKismetMathLibrary::Max(LeftFootOffset, RightFootOffset), DeltaTime, InterpSpeed);

	LeftFootRotation = F_CalculateRotationOffset(LeftFootRotation, LeftFloorNormal, DeltaTime);
	RightFootRotation = F_CalculateRotationOffset(RightFootRotation, RightFloorNormal, DeltaTime);

}

float UIk_Manager::GetLeftOffset()
{
	return USunLibraryBPLibrary::F_Minus(LeftFootOffset);
}

float UIk_Manager::GetRightOffset()
{
	return USunLibraryBPLibrary::F_Minus(RightFootOffset);
}

float UIk_Manager::GetPelvisOffset()
{
	return USunLibraryBPLibrary::F_Minus(PelvisOffset);
}

FRotator UIk_Manager::GetLeftRotation()
{
	return LeftFootRotation;
}

FRotator UIk_Manager::GetRightRotation()
{
	return RightFootRotation;
}

void UIk_Manager::F_TraceFromFoot(FName BoneName, float TraceBelowCapsule, float& Offset, FVector& ImpactNormal)
{
	if (PlayerRef == NULL)
	{
		Offset = 0.f;
		ImpactNormal = FVector(0.f);
		return;
	}
	FVector BoneLocation = PlayerRef->GetMesh()->GetSocketLocation(BoneName);
	FVector StartTrace = FVector(BoneLocation.X, BoneLocation.Y, PlayerRef->GetActorLocation().Z);
	float ZEndTrace = PlayerRef->GetActorLocation().Z - (PlayerRef->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + TraceBelowCapsule);
	FVector EndTrace = FVector(BoneLocation.X, BoneLocation.Y, ZEndTrace);

	FHitResult OutHit;
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	bool bIsHitSomething = GetWorld()->LineTraceSingleByChannel(OutHit, StartTrace, EndTrace, ECC_Visibility, Params);
	
	Offset = 0.f;
	ImpactNormal = OutHit.ImpactNormal;
	if (bIsHitSomething)
	{
		Offset = ((StartTrace - OutHit.Location).Size()) - PlayerRef->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	}
	return;
}

FRotator UIk_Manager::F_CalculateRotationOffset(FRotator CurrentRotation, FVector FloorNormal, float DeltaSeconds)
{
	FVector Axis = FVector::CrossProduct(PlayerRef->GetActorUpVector(), FloorNormal);
	float DotVector = FVector::DotProduct(PlayerRef->GetActorUpVector(), FloorNormal);
	FRotator TargetRotator = UKismetMathLibrary::RotatorFromAxisAndAngle(Axis, UKismetMathLibrary::DegAcos(DotVector));
	return UKismetMathLibrary::RInterpTo_Constant(CurrentRotation, TargetRotator, DeltaSeconds, InterpSpeed);
}


