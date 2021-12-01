// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slide.generated.h"

/**
 * 
 */
UCLASS()
class SUNLIBRARY_API USlide : public UUserWidget
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChange, float, Value);

		virtual bool Initialize();

private:

	UFUNCTION()
	void FSetDisplayPercentage(float Value);

protected:

	UPROPERTY(BlueprintReadOnly)
	FText CurrentText;

	UPROPERTY(meta = (BindWidget))
		class USlider* Slider;

	UPROPERTY(meta =(BindWidget))
		class UTextBlock* TextPercent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Value"))
	float CurrentValue;

protected:

	UPROPERTY(EditAnywhere)
		float StepSize;

	UPROPERTY(EditAnywhere)
		float MinValue;

	UPROPERTY(EditAnywhere)
		float MaxValue;

public:

	UPROPERTY(BlueprintAssignable)
	FOnChange OnChange;

	UPROPERTY()
	FGetFloat CurrentValueDelegate;

	PROPERTY_BINDING_IMPLEMENTATION(float, CurrentValue);
};