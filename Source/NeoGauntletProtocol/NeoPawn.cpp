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

UAbilitySystemComponent* ANeoPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ANeoPawn::OnMoveTriggered(const FInputActionValue& Value)
{
	// Debug print the movement vector
	const FVector MovementVector = Value.Get<FVector>();
	UE_LOG(LogTemp, Warning, TEXT("Movement Vector: %s"), *MovementVector.ToString());
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
