// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SunLibraryBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

class UComboBoxString;
class UInputKeySelector;

UCLASS()
class USunLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	//Ajout toutes les resolutions possible a un combo string.
	//Et recupere celle qui est actuellement utiliser pour set l'option du Combo string par defaut.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddResolution", Keywords = "Resolution"), Category = "Affichage")
		static void F_AddResolution(UComboBoxString* target);

	//Utiliser pour ajoute les differents screen mode a un combo string
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddScreenMode", Keywords = "ScreenMode"), Category = "Affichage")
		static void F_AddScreenMode(UComboBoxString* target);

	//Set une resolution a partir d'un string.
	//	EX : 1920 x 1080
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetResolution", Keywords = "Resolution"), Category = "Affichage")
		static void F_SetResolution(FString SourceString);

	//Utiliser pour set un Screen mode
	//	A partir d'un comboBox
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetScreenMode", Keywords = "ScreenMode"), Category = "Affichage")
		static void F_SetScreenMode(UComboBoxString* target);

	//Set L'Input selectionner de l'InputKeySelector
	//En fonction de Action Name
	// 
	// /!\ Attention cet fonction ne prennd pas en compte si il y a plusieurs /!\
	//touche avec le meme scale
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetAction", Keywords = "Action"), Category = "KeyBind")
		static void F_SetAction(UInputKeySelector* Target, FName InActionName, bool bManette);

	//Set L'Input selectionner de l'InputKeySelector
	//En fonction de Axis Name et du Scale
	// 
	//		/!\ Attention cet fonction ne prennd pas en compte si il y a plusieurs /!\
	//			touche avec le meme scale
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetAxis", Keywords = "Axis"), Category = "KeyBind")
		static void F_SetAxis(UInputKeySelector* Target, FName InAxisName, float Scale, bool bManette);
	
	//Bind InputChord a l'ActionName donner
	//Et supprime l'ancinne action mappings
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "BindAction", Keywords = "Action"), Category = "KeyBind")
		static void F_BindAction(FInputChord InputChord, FName InActionName, bool bManette);

	//Bind InputChord a l'AxisName donner
	//Et supprime l'ancinne axis mappings
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "BindAxis", Keywords = "Axis"), Category = "KeyBind")
		static void F_BindAxis(FInputChord InputChord, FName InAxisName, float Scale, bool bManette);

	//Cherche si l'input donner n'est pas deja utiliser dans un action mappings
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "IsAnySameAction", Keywords = "Action"), Category = "KeyBind")
		static bool F_IsAnyActionSame(FInputChord InputChord, FName InName);

	//Cherche si l'input donner n'est pas deja utiliser dans un axis mappings
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "IsAnySameAxis", Keywords = "Axis"), Category = "KeyBind")
		static bool F_IsAnyAxisSame(FInputChord InputChord, float Scale, FName InName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DisplayWidget", Keywords = "Widget"), Category = "Widget")
		static void F_DisplayWidget(TSubclassOf<UUserWidget>ClassWidget, APlayerController* PlayerController, UUserWidget*& ReturnValue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveWidget", Keywords = "Widget"), Category = "Widget")
		static void F_RemoveWidget(UUserWidget* Target, APlayerController* PlayerController);

	UFUNCTION(meta = (DisplayName = "AddQuality", Keywords = "Quality"), Category="Widget")
	static void F_AddQuality(UComboBoxString* target);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddShadowResolution", Keywords = "Shadow"), Category = "Widget")
		static void  F_AddShadowResolution(UComboBoxString* target);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddOverallSettings", Keywords = "Overall"), Category = "Widget")
	static void F_AddOverall(UComboBoxString* target);
};
