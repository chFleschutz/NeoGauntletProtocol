// Christoph Fleschutz

#pragma once

#include "CoreMinimal.h"
#include "MovementMode.h"
#include "NeoWalkingMode.generated.h"

/**
 * 
 */
UCLASS()
class NEOGAUNTLETPROTOCOL_API UNeoWalkingMode : public UBaseMovementMode
{
	GENERATED_BODY()
	
public:
	virtual void OnGenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;
	virtual void OnSimulationTick(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;
};
