// Fill out your copyright notice in the Description page of Project Settings.


#include "WheelSelect.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UWheelSelect::Initialize()
{
	Super::Initialize();
	BLeft->OnClicked.AddDynamic(this, &UWheelSelect::BLeftClick);
	BRight->OnClicked.AddDynamic(this, &UWheelSelect::BRightClick);
	F_SetSelectedIndex(DefaultOption);

	return true;
}

void UWheelSelect::F_MoveWheel(int Value)
{
	if (Options.Num()<=0)
	{
		return;
	}
	BLeft->SetIsEnabled(true);
	BRight->SetIsEnabled(true);
	SelectIndex += Value;
	if (bLoop)
	{
		if (SelectIndex > Options.Num()-1)
		{
			SelectIndex = 0;
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
		}
		else
		{
			if (SelectIndex < 0)
			{
				SelectIndex = Options.Num() - 1;
			}
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
		}
	}
	else
	{
		if (SelectIndex >= Options.Num() - 1)
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
				SelectIndex = Options.Num() - 1;
				BLeft->SetIsEnabled(false);
			}
			DisplayText = Options[SelectIndex];
			Text_C->SetText(DisplayText);
		}
	}
	//Ici Tu met ton event Dispatcher
	OnChange.Broadcast(SelectIndex);
	return;
}

void UWheelSelect::F_SetSelectedIndex(int Index = 0)
{
	if (Options.Num() <= 0)
	{
		return;
	}
	BLeft->SetIsEnabled(true);
	BRight->SetIsEnabled(true);
	if (Index <= 0)
	{
		SelectIndex = 0;
		if (!bLoop)
		{
			BLeft->SetIsEnabled(false);
		}
	}
	else if(Index >= Options.Num()-1)
	{
		SelectIndex = Options.Num() - 1;
		if (!bLoop)
		{
			BRight->SetIsEnabled(false);
		}
	}
	else
	{
		SelectIndex = Index;
	}
	DisplayText = Options[SelectIndex];
	Text_C->SetText(DisplayText);
	return;
}

int UWheelSelect::F_GetSelectedIndex()
{
	return SelectIndex;
}

bool UWheelSelect::IsLoopEnable()
{
	return bLoop;
}

void UWheelSelect::BLeftClick()
{
	F_MoveWheel(-1);
	return;
}

void UWheelSelect::BRightClick()
{
	F_MoveWheel(1);
	return;
}

bool UWheelSelect::LeftIsEnable()
{
	return BLeft->bIsEnabled;
}

bool UWheelSelect::RightIsEnable()
{
	return BRight->bIsEnabled;
}