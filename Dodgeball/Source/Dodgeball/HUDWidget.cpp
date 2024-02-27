// Fill out your copyright notice in the Description page of Project Settings.

#include "Components//ProgressBar.h"
#include "HUDWidget.h"

void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}
