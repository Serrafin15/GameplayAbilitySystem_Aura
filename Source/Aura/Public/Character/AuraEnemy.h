// Copyright Alex Dominguez

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction\EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	virtual void HighlightActor() override; // Overriden from IEnemyInterface
	virtual void UnHighlightActor() override; // Overriden from IEnemyInterface

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
};
