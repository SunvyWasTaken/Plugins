// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/KeyModifier.h"
#include "GameFramework/InputSettings.h"
#include "Components/TextBlock.h"
#include "Components/InputKeySelector.h"

bool UKeyModifier::Initialize()
{
	Super::Initialize();

	if (IKAction != nullptr)
	{
		IKAction->SetSelectedKey(Keyboard);
		IKAction->OnKeySelected.AddDynamic(this, &UKeyModifier::ChangeKey);
	}
	return true;
}

void UKeyModifier::SetInitialkey()
{
	IKAction->SetSelectedKey(Keyboard);
	return;
}

void UKeyModifier::ChangeKey(FInputChord SelectedKey)
{
	if (CheckIfHasKey(SelectedKey.Key))
	{
		if (Scale != 0)
		{
			FInputAxisKeyMapping CurrentKey = FInputAxisKeyMapping(AName, Keyboard, Scale);
			UInputSettings::GetInputSettings()->RemoveAxisMapping(CurrentKey, true);
			FInputAxisKeyMapping NewKey = FInputAxisKeyMapping(AName, SelectedKey.Key, Scale);
			UInputSettings::GetInputSettings()->AddAxisMapping(NewKey, true);
			Keyboard = SelectedKey.Key;
			return;
		}
		else
		{
			FInputActionKeyMapping CurrentKey = FInputActionKeyMapping(AName, Keyboard);
			UInputSettings::GetInputSettings()->RemoveActionMapping(CurrentKey, true);
			FInputActionKeyMapping NewKey = FInputActionKeyMapping(AName, SelectedKey.Key);
			UInputSettings::GetInputSettings()->AddActionMapping(NewKey, true);
			Keyboard = SelectedKey.Key;
			return;
		}
	}
	IKAction->SetSelectedKey(Keyboard);
	return;
}

bool UKeyModifier::CheckIfHasKey(FKey CurrentKey)
{
	TArray<FName> AxisName;
	UInputSettings::GetInputSettings()->GetAxisNames(AxisName);
	for (int i = 0; i < AxisName.Num(); i++)
	{
		TArray<FInputAxisKeyMapping> KeyAxisMapping;
		UInputSettings::GetInputSettings()->GetAxisMappingByName(AxisName[i], KeyAxisMapping);
		for (int a = 0; a < KeyAxisMapping.Num(); a++)
		{
			if (KeyAxisMapping[a].Key == CurrentKey)
			{
				return false;
			}
		}
	}
	TArray<FName> ActionName;
	UInputSettings::GetInputSettings()->GetActionNames(ActionName);
	for (int i = 0; i < ActionName.Num(); i++)
	{
		TArray<FInputActionKeyMapping> KeyActionMapping;
		UInputSettings::GetInputSettings()->GetActionMappingByName(ActionName[i], KeyActionMapping);
		for (int a = 0; a < KeyActionMapping.Num(); a++)
		{
			if (KeyActionMapping[a].Key == CurrentKey)
			{
				return false;
			}
		}
	}
	return true;
}