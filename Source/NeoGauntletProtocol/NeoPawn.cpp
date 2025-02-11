// Christoph Fleschutz


#include "NeoPawn.h"


ANeoPawn::ANeoPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("AttributeSet"));
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

}

UAbilitySystemComponent* ANeoPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
