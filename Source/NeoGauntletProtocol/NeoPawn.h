// Christoph Fleschutz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "MoverComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "PlayerAttributeSet.h"

#include "NeoPawn.generated.h"

UCLASS()
class NEOGAUNTLETPROTOCOL_API ANeoPawn : 
	public APawn, 
	public IAbilitySystemInterface,
	public IMoverInputProducerInterface
{
	GENERATED_BODY()

public:
	ANeoPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UPlayerAttributeSet> AttributeSet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UMoverComponent> MoverComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookInputAction;

private:
	void OnMoveTriggered(const FInputActionValue& Value);
	void OnMoveCompleted(const FInputActionValue& Value);
	void OnLookTriggered(const FInputActionValue& Value);
	void OnLookCompleted(const FInputActionValue& Value);

	FVector3d CachedMoveInput = FVector3d::ZeroVector;
};
