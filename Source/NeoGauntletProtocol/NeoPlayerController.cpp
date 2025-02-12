// Christoph Fleschutz


#include "NeoPlayerController.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void ANeoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) // Only deal with input if we're the local player
		return;
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (TObjectPtr<UInputMappingContext>& CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}
