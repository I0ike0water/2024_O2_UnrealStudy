// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "O2Character.generated.h"

UCLASS()
class UNREALSTUDY_API AO2Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AO2Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Input)
		TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Input)
		TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Input)
		TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Input)
		TObjectPtr<class UInputAction> LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;
};
