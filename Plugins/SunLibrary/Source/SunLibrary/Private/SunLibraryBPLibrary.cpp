// Copyright Epic Games, Inc. All Rights Reserved.

#include "SunLibraryBPLibrary.h"
#include "SunLibrary.h"
#include "GameFramework/InputSettings.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ComboBoxString.h"
#include "Components/InputKeySelector.h"

USunLibraryBPLibrary::USunLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void USunLibraryBPLibrary::F_AddResolution(UComboBoxString* target)
{
	TArray<FIntPoint> TResolution;
	//Recupe toute les résolutions possible que peut supporter l'ordinateur.
	if (UKismetSystemLibrary::GetSupportedFullscreenResolutions(TResolution))
	{
		//Pour chaque résolution disponible
		for (int i = 0; i < TResolution.Num(); i++)
		{
			FIntPoint CurrentResolution = TResolution[i];
			FString A = FString::FromInt(CurrentResolution.X);
			FString B = FString::FromInt(CurrentResolution.Y);	
			//Crée un string. Ex: 1920 x 1080
			FString Resolution = A + " x " + B;
			//Ajout l'option au target
			target->AddOption(Resolution);
		}
		//Set l'option selectionner en fonction des setting actuelle
		FIntPoint CurrentResolution = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
		FString A = FString::FromInt(CurrentResolution.X);
		FString B = FString::FromInt(CurrentResolution.Y);
		FString Resolution = A + " x " + B;
		target->SetSelectedOption(Resolution);
		return;
	}
	return;
}

void USunLibraryBPLibrary::F_AddScreenMode(UComboBoxString* target)
{
	for (size_t i = 0; i < EWindowMode::NumWindowModes; i++)
	{
		EWindowMode::Type CurrentWindowMode;
		CurrentWindowMode = EWindowMode::ConvertIntToWindowMode(i);
		FString CurrentMode = UEnum::GetValueAsString(CurrentWindowMode).RightChop(13);
		target->AddOption(CurrentMode);
	}
	return;
}

void USunLibraryBPLibrary::F_SetResolution(FString SourceString)
{
	TArray<FIntPoint> TResolution;
	TArray<FString> FResolution;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(TResolution);
	for (int i = 0; i < TResolution.Num(); i++)
	{
		FIntPoint CurrentResolution = TResolution[i];
		FString A = FString::FromInt(CurrentResolution.X);
		FString B = FString::FromInt(CurrentResolution.Y);
		FString SResolution = A + " x " + B;
		if (SResolution == SourceString)
		{
			UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
			UserSettings->SetScreenResolution(TResolution[i]);
			UserSettings->ApplyResolutionSettings(true);
			UserSettings->SaveSettings();
			return;
		}
	}
	return;
}

void USunLibraryBPLibrary::F_SetScreenMode(UComboBoxString* target)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	EWindowMode::Type TargetWindowMode = EWindowMode::ConvertIntToWindowMode(target->GetSelectedIndex());
	UserSettings->SetFullscreenMode(TargetWindowMode);
	UserSettings->ApplySettings(true);
	UserSettings->SaveSettings();
	return;
}

void USunLibraryBPLibrary::F_SetAction(UInputKeySelector* Target, FName InActionName, bool bManette)
{
	UInputSettings* InputSetting = UInputSettings::GetInputSettings();
	TArray<FInputActionKeyMapping> OutMapping;
	InputSetting->GetActionMappingByName(InActionName, OutMapping);
	for (int i = 0; i < OutMapping.Num(); i++)
	{
		if (OutMapping[i].Key.IsGamepadKey() == bManette)
		{
			FInputChord NewKey = FInputChord(OutMapping[i].Key, OutMapping[i].bShift, OutMapping[i].bCtrl, OutMapping[i].bAlt, OutMapping[i].bCmd);
			Target->SetSelectedKey(NewKey);
			return;
		}
	}
	return;
}

void USunLibraryBPLibrary::F_SetAxis(UInputKeySelector* Target, FName InAxisName, float Scale, bool bManette)
{
	UInputSettings* InputSetting = UInputSettings::GetInputSettings();
	TArray<FInputAxisKeyMapping> OutMapping;
	InputSetting->GetAxisMappingByName(InAxisName, OutMapping);
	for (int i = 0; i < OutMapping.Num(); i++)
	{
		if (OutMapping[i].Scale == Scale && OutMapping[i].Key.IsGamepadKey() == bManette)
		{
			Target->SetSelectedKey(OutMapping[i].Key);
			return;
		}
	}
	return;
}

void USunLibraryBPLibrary::F_BindAction(FInputChord InputChord, FName InActionName, bool bManette)
{
	UInputSettings* InputSetting = UInputSettings::GetInputSettings();
	TArray<FInputActionKeyMapping> OutMapping;
	InputSetting->GetActionMappingByName(InActionName,OutMapping);
	for (int i = 0; i < OutMapping.Num(); i++)
	{
		if (OutMapping[i].Key.IsGamepadKey() == bManette)
		{
			InputSetting->RemoveActionMapping(OutMapping[i], true);
			FInputActionKeyMapping NewKey = FInputActionKeyMapping(InActionName, InputChord.Key, InputChord.bShift, InputChord.bCtrl, InputChord.bAlt, InputChord.bCmd);
			InputSetting->AddActionMapping(NewKey, true);
			InputSetting->SaveKeyMappings();
			return;
		}
	}
	FInputActionKeyMapping NewKey = FInputActionKeyMapping(InActionName, InputChord.Key, InputChord.bShift, InputChord.bCtrl, InputChord.bAlt, InputChord.bCmd);
	InputSetting->AddActionMapping(NewKey, true);
	InputSetting->SaveKeyMappings();
	return;
}

void USunLibraryBPLibrary::F_BindAxis(FInputChord InputChord, FName InAxisName, float Scale, bool bManette)
{
	UInputSettings* InputSetting = UInputSettings::GetInputSettings();
	TArray<FInputAxisKeyMapping> OutMapping;
	InputSetting->GetAxisMappingByName(InAxisName, OutMapping);
	for (int i = 0; i < OutMapping.Num(); i++)
	{
		if (OutMapping[i].Scale == Scale && OutMapping[i].Key.IsGamepadKey() == bManette)
		{
			InputSetting->RemoveAxisMapping(OutMapping[i], true);
			FInputAxisKeyMapping NewKey = FInputAxisKeyMapping(InAxisName, InputChord.Key, Scale);
			InputSetting->AddAxisMapping(NewKey, true);
			InputSetting->SaveKeyMappings();
			return;
		}
	}
	FInputAxisKeyMapping NewKey = FInputAxisKeyMapping(InAxisName, InputChord.Key, Scale);
	InputSetting->AddAxisMapping(NewKey, true);
	InputSetting->SaveKeyMappings();
	return;
}

bool USunLibraryBPLibrary::F_IsAnyActionSame(FInputChord InputChord, FName InName)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	TArray<FName> TActionNames;
	InputSettings->GetActionNames(TActionNames);
	for (int i = 0; i < TActionNames.Num(); i++)
	{
		if (TActionNames[i] != InName)
		{
			TArray<FInputActionKeyMapping> OutMapping;
			InputSettings->GetActionMappingByName(TActionNames[i], OutMapping);
			for (int a = 0; a < OutMapping.Num(); a++)
			{
				FInputChord CompardKey = FInputChord(OutMapping[i].Key, OutMapping[i].bShift, OutMapping[i].bCtrl, OutMapping[i].bAlt, OutMapping[i].bCmd);
					if (CompardKey == InputChord)
					{
						return true;
					}
			}
		}
	}
	return false;
}

bool USunLibraryBPLibrary::F_IsAnyAxisSame(FInputChord InputChord, float Scale, FName InName)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	TArray<FName> TAxisNames;
	InputSettings->GetActionNames(TAxisNames);
	TArray<FInputAxisKeyMapping> OutMapping;
	for (int i = 0; i < TAxisNames.Num(); i++)
	{
		if (TAxisNames[i] != InName)
		{
			InputSettings->GetAxisMappingByName(TAxisNames[i], OutMapping);
			for (int a = 0; a < OutMapping.Num(); a++)
			{
				if (OutMapping[a].Key == InputChord.Key)
				{
					return true;
				}
			}
		}
		else
		{
			InputSettings->GetAxisMappingByName(InName, OutMapping);
			for (int a = 0; a < OutMapping.Num(); a++)
			{
				if (OutMapping[a].Scale != Scale)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void USunLibraryBPLibrary::F_DisplayWidget(TSubclassOf<UUserWidget>ClassWidget, APlayerController* PlayerController,UUserWidget*& ReturnValue)
{
	//UUserWidget* CurrentWidget = CreateWidget(PlayerController, ClassWidget);
	//ReturnValue = CurrentWidget;
	//CurrentWidget->AddToViewport();
	//PlayerController->bShowMouseCursor = true;
	//UWidgetBlueprintLibrary::SetInputMode_UIOnly(PlayerController,CurrentWidget);
	return;
}

void USunLibraryBPLibrary::F_RemoveWidget(UUserWidget* Target, APlayerController* PlayerController)
{
	Target->RemoveFromParent();
	PlayerController->bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	return;
}
