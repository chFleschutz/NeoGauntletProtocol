// Christoph Fleschutz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NeoPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class NEOGAUNTLETPROTOCOL_API ANeoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;
};
