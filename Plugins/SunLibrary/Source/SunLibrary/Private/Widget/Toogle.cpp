// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Toogle.h"
#include "Components/Button.h"

bool UToogle::Initialize()
{
	Super::Initialize();
	FToogle();
	MainButton->OnClicked.AddDynamic(this, &UToogle::FToogle);
	return true;
}

void UToogle::FToogle()
{
	if (bIsOn)
	{
		bIsOn = 0;
	}
	else
	{
		bIsOn = 1;
	}
	AOnChange(bIsOn);
	OnChange.Broadcast(bIsOn);
	return;
}

void UToogle::AOnChange_Implementation(bool value)
{

}