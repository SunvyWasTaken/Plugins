// Fill out your copyright notice in the Description page of Project Settings.


#include "Slide.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

bool USlide::Initialize()
{
	Super::Initialize();
	Slider->SetStepSize(StepSize);
	Slider->SetMinValue(MinValue);
	Slider->SetMaxValue(MaxValue);
	Slider->OnValueChanged.AddDynamic(this, &USlide::FSetDisplayPercentage);
	return true;
}

void USlide::FSetDisplayPercentage(float value)
{
	CurrentValue = value;
	OnChange.Broadcast(value);
	FNumberFormattingOptions* Option = new FNumberFormattingOptions();
	Option->SetAlwaysSign(false);
	Option->SetUseGrouping(true);
	Option->SetMinimumFractionalDigits(0);
	Option->SetMaximumFractionalDigits(0);
	CurrentText = FText::AsPercent(value, Option);
	return;
}
