// Fill out your copyright notice in the Description page of Project Settings.


#include "WheelSelect.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UWheelSelect::Initialize()
{
	Super::Initialize();
	//this->GetDesiredTickFrequency();
	Text_C->SetText(DisplayText);
	BLeft->OnClicked.AddDynamic(this, &UWheelSelect::BLeftClick);
	BRight->OnClicked.AddDynamic(this, &UWheelSelect::BRightClick);

	return true;
}

void UWheelSelect::MoveWheel(int Value)
{
	BLeft->SetIsEnabled(true);
	BRight->SetIsEnabled(true);
	SelectIndex += Value;
	if (bLoop)
	{
		if (SelectIndex>Options.Num())
		{
			SelectIndex = 0;
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
		}
		else
		{
			if (SelectIndex<0)
			{
				SelectIndex = Options.Num();
			}
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
		}
	}
	else
	{
		if (SelectIndex >= Options.Num())
		{
			SelectIndex = 0;
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
			BRight->SetIsEnabled(false);
		}
		else
		{
			if (SelectIndex <= 0)
			{
				SelectIndex = Options.Num();
				BLeft->SetIsEnabled(false);
			}
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
		}
	}
	//Ici Tu met ton event Dispatcher
	return;
}

void UWheelSelect::BLeftClick()
{
	MoveWheel(-1);
	return;
}

void UWheelSelect::BRightClick()
{
	MoveWheel(1);
	return;
}