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
	void FOnChangeSlide(float Value);

	UFUNCTION()
	void FSetDisplayPercentage(float Value);

protected:

	UFUNCTION(BlueprintNativeEvent, meta=(DisplayName ="CustomText"))
	void FCustomText(float Value);

	UPROPERTY(BlueprintReadOnly, Category = "Property")
	FText CurrentText;

	UPROPERTY(meta = (BindWidget))
	class USlider* Slider;

	UPROPERTY(meta =(BindWidget))
	class UTextBlock* TextPercent;

protected:

	UPROPERTY(EditAnywhere, Category = "Property")
	float StepSize;

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Property")
	bool IsCustomText = 0;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "IsCustomText"), AdvancedDisplay, Category = "Property")
	float MinValue;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "IsCustomText"), AdvancedDisplay, Category = "Property")
	float MaxValue;

public:

	UPROPERTY(BlueprintAssignable)
	FOnChange OnChange;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value"), Category = "Property")
		float CurrentValue;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Value"), Category = "Property")
		void FSetValue(float value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Custom Text"), Category = "Property")
	void FSetText(FText text);

	UPROPERTY()
	FGetFloat CurrentValueDelegate;

	PROPERTY_BINDING_IMPLEMENTATION(float, CurrentValue);
};
