// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/O2GameMode.h"

AO2GameMode::AO2GameMode()
{
	ConstructorHelpers::FClassFinder<APawn>DefaultPawnClassRef("/Game/Blueprint/Character");

	if (DefaultPawnClassRef) {}
	//ConstructorHelpers::FClassFinder<APawn>
	//ConstructorHelpers::FClassFinder<APlayerController>
}
