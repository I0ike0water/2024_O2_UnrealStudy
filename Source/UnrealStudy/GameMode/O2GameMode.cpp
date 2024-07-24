// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/O2GameMode.h"

AO2GameMode::AO2GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprint/Character/BP_PlayerCharacter.BP_PlayerCharacter"));
	if (DefaultPawnClassRef.Class) {
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef (TEXT("/Script/UnrealStudy.O2PlayerController"));
	if (PlayerControllerClassRef.Class) {
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
