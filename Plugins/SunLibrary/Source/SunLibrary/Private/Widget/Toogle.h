// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Toogle.generated.h"

/**
 * 
 */
UCLASS()
class UToogle : public UUserWidget
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChange, bool, value);

		virtual bool Initialize();

private:

	UPROPERTY(meta=(BindWidget))
	class UImage* Background;

	UPROPERTY(meta = (BindWidget))
	class UImage* cercle;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainButton;

public:

	UFUNCTION()
	void FToogle();

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName="Is On"), Category = "Property")
	bool bIsOn;

	UFUNCTION(BlueprintNativeEvent, Category ="Custom")
	void AOnChange(bool value);

	UPROPERTY(BlueprintAssignable)
	FOnChange OnChange;

};
