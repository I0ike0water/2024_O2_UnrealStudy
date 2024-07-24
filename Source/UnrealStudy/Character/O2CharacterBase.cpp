// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/O2CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AO2CharacterBase::AO2CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(50.f, 100.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.32f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


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
void AO2CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AO2CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AO2CharacterBase::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AO2CharacterBase::Look);
}

// Called every frame
void AO2CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AO2CharacterBase::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDiraction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDiraction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDiraction, MovementVector.X);
	AddMovementInput(RightDiraction, MovementVector.Y);
}

void AO2CharacterBase::Look(const FInputActionValue& Value) {
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}


