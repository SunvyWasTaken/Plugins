// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Slide.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

bool USlide::Initialize()
{
	Super::Initialize();
	Slider->SetStepSize(StepSize);
	if (IsCustomText)
	{
		Slider->SetMinValue(MinValue);
		Slider->SetMaxValue(MaxValue);
	}
	else
	{
		Slider->SetMinValue(0);
		Slider->SetMaxValue(1);
		FSetDisplayPercentage(CurrentValue);
	}
	Slider->OnValueChanged.AddDynamic(this, &USlide::FOnChangeSlide);
	return true;
}

void USlide::FOnChangeSlide(float Value)
{
	OnChange.Broadcast(Value);
	CurrentValue = Value;
	if (!IsCustomText)
	{
		FSetDisplayPercentage(Value);
	}
	else
		FCustomText(Value);
	return;
}

void USlide::FSetDisplayPercentage(float value)
{
	FNumberFormattingOptions* Option = new FNumberFormattingOptions();
	Option->SetAlwaysSign(false);
	Option->SetUseGrouping(true);
	Option->SetMinimumFractionalDigits(0);
	Option->SetMaximumFractionalDigits(0);
	CurrentText = FText::AsPercent(value, Option);
	return;
}

void USlide::FCustomText_Implementation(float Value)
{
	return;
}

void USlide::FSetValue(float value)
{
	CurrentValue = value;
	FSetDisplayPercentage(CurrentValue);
	return;
}

void USlide::FSetText(FText text)
{
	CurrentText = text;
	return;
}
