// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyModifier.generated.h"

/**
 * 
 */
UCLASS()
class SUNLIBRARY_API UKeyModifier : public UUserWidget
{
	GENERATED_BODY()

		virtual bool Initialize();

private:

	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox*Canvas;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ActionText;

	UPROPERTY(meta=(BindWidget))
	class UInputKeySelector* IKAction;

	UFUNCTION(BlueprintCallable, Category="Custom")
		void SetInitialkey();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void ChangeKey(FInputChord SelectedKey);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Custom")
	bool CheckIfHasKey(FKey CurrentKey);

public:

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"), Category = "Property")
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true", DisplayName ="Name"), Category = "Property")
	FName AName;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Property")
	FKey Keyboard;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Property")
	float Scale;

};
