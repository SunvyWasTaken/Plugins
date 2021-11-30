// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WheelSelect.generated.h"

/**
 * Roue de selection personnaliser
 */
UCLASS()
class SUNLIBRARY_API UWheelSelect : public UUserWidget
{
	GENERATED_BODY()

		virtual bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* BLeft;

	UPROPERTY(meta = (BindWidget))
	class UButton* BRight;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_C;

	UFUNCTION()
	void BLeftClick();

	UFUNCTION()
	void BRightClick();

	UFUNCTION()
	void MoveWheel(int Value);

	UPROPERTY()
	int SelectIndex;

public:

	UPROPERTY(EditAnywhere)
	FText DisplayText;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool bLoop;

	UPROPERTY(EditAnywhere)
	TArray<FText> Options;

	UPROPERTY(EditAnywhere)
	FText DefaultOption;
	
};
