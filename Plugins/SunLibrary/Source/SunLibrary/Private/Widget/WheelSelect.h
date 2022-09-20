// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WheelSelect.generated.h"

/**
 * Roue de selection personnaliser
 */
UCLASS(meta=(DisplayName="Wheel Selector"))
class SUNLIBRARY_API UWheelSelect : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChange,int,index);

		virtual bool Initialize();

		virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent);

private:

	UPROPERTY()
	int SelectIndex;

	UFUNCTION()
	void BLeftClick();

	UFUNCTION()
	void BRightClick();

protected:

	UPROPERTY()
	FText DisplayText;

	UFUNCTION(BlueprintCallable, meta=(DisplayName="MoveWheel"), Category = "Custom")
	void F_MoveWheel(int Value);

	UPROPERTY(meta = (BindWidget))
	class UButton* BLeft;

	UPROPERTY(meta = (BindWidget))
	class UButton* BRight;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_C;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "Custom")
	class UButton* BForGamepad;

public:
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName="SetIndex", Keywords="Index"), Category = "Custom")
	void F_SetSelectedIndex(int Index);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetIndex", Keywords = "Index"), Category = "Custom")
	int F_GetSelectedIndex();

	UFUNCTION(BlueprintPure, Category = "Property")
	bool IsLoopEnable();

	UFUNCTION(BlueprintPure, Category = "Property")
	bool LeftIsEnable();

	UFUNCTION(BlueprintPure, Category = "Property")
	bool RightIsEnable();

	UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Option", KeyWords="Add"), Category="Variable")
	void F_AddOption(FText option);

	UPROPERTY(BlueprintAssignable)
	FOnChange OnChange;

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Property")
	bool bLoop;

	UPROPERTY(EditAnywhere, Category = "Property")
	TArray<FText> Options;

	UPROPERTY(EditAnywhere, Category = "Property")
	int32 DefaultOption;

	/** A bindable delegate to allow logic to drive the text of the widget */
	UPROPERTY()
	FGetInt32 DefaultOptionDelegate;

	protected:

		PROPERTY_BINDING_IMPLEMENTATION(int32, DefaultOption);
	
};
