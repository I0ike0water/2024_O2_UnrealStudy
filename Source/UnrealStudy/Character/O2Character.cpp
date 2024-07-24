// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/O2Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AO2Character::AO2Character()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/IMC_Default.IMC_Default'"));

	if (InputMappingContextRef.Object) {
		InputMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/BluePrint/Input/IA_Move.IA_Move'"));
	
	if (MoveActionRef.Object) {
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/BluePrint/Input/IA_Look.IA_Look'"));

	if (LookActionRef.Object) {
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/BluePrint/Input/IA_Jump.IA_Jump'"));

	if (JumpActionRef.Object) {
		JumpAction = JumpActionRef.Object;
	}
}

// Called when the game starts or when spawned
void AO2Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AO2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AO2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

