// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"
#include "RestartWidget.h"
#include "DodgeballPlayerController.h"

void ADodgeballPlayerController::ShowRestartWidget()
{
	if(BP_RestartWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	bShowMouseCursor = false;
	SetInputMode((FInputModeGameOnly()));
	SetPause(false);
}

void ADodgeballPlayerController::UpdateHealthPercent(float HealthPercent)
{
	if(HUDWidget != nullptr)
	{
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}

void ADodgeballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if( BP_HUDWidget != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}
