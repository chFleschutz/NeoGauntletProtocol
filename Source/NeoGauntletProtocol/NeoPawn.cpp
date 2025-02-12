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
	
}

void ANeoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	
	FString msg = FString::Printf(TEXT("Move %s"), *CachedMoveInput.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, msg);

	CharacterInputs.SetMoveInput(EMoveInputType::DirectionalIntent, CachedMoveInput);
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
}

void ANeoPawn::OnLookTriggered(const FInputActionValue& Value)
{
}

void ANeoPawn::OnLookCompleted(const FInputActionValue& Value)
{
}
