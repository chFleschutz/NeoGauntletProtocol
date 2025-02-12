// Christoph Fleschutz


#include "NeoPawn.h"


ANeoPawn::ANeoPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(false); // Mover handles movement replication

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("AttributeSet"));
	
	MoverComponent = CreateDefaultSubobject<UMoverComponent>(TEXT("MoverComponent"));
}

void ANeoPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		PC->PlayerCameraManager->ViewPitchMax = 89.0f;
		PC->PlayerCameraManager->ViewPitchMin = -89.0f;
	}
}

void ANeoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		static const float LookRateYaw = 100.0f;
		static const float LookRatePitch = 100.0f;
		PC->AddYawInput(CachedLookInput.Yaw * LookRateYaw * DeltaTime);
		PC->AddPitchInput(-CachedLookInput.Pitch * LookRatePitch * DeltaTime);
	}

	CachedLookInput = FRotator3d::ZeroRotator;
}

void ANeoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ANeoPawn::OnMoveTriggered);
		Input->BindAction(MoveInputAction, ETriggerEvent::Completed, this, &ANeoPawn::OnMoveCompleted);
		Input->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ANeoPawn::OnLookTriggered);
		Input->BindAction(LookInputAction, ETriggerEvent::Completed, this, &ANeoPawn::OnLookCompleted);
	}
}

void ANeoPawn::ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult)
{
	FCharacterDefaultInputs& CharacterInputs = InputCmdResult.InputCollection.FindOrAddMutableDataByType<FCharacterDefaultInputs>();

	if (!GetController())
	{
		if (GetLocalRole() == ENetRole::ROLE_Authority && GetRemoteRole() == ENetRole::ROLE_SimulatedProxy)
		{
			static const FCharacterDefaultInputs DoNothingInput;
			CharacterInputs = DoNothingInput;
		}
		return;
	}

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		CharacterInputs.ControlRotation = PC->GetControlRotation();
	}

	FVector finalMoveInput = CharacterInputs.ControlRotation.RotateVector(CachedMoveInput);
	CharacterInputs.SetMoveInput(EMoveInputType::DirectionalIntent, finalMoveInput);
}

UAbilitySystemComponent* ANeoPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ANeoPawn::OnMoveTriggered(const FInputActionValue& Value)
{
	CachedMoveInput = FVector3d(Value.Get<FVector>());
}

void ANeoPawn::OnMoveCompleted(const FInputActionValue& Value)
{
	CachedMoveInput = FVector3d::ZeroVector;
}

void ANeoPawn::OnLookTriggered(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	CachedLookInput.Yaw = LookInput.X;
	CachedLookInput.Pitch = LookInput.Y;
}

void ANeoPawn::OnLookCompleted(const FInputActionValue& Value)
{
	CachedLookInput = FRotator3d::ZeroRotator;
}
