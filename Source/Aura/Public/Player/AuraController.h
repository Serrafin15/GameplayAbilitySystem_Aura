// Copyright Alex Dominguez

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction\EnemyInterface.h"
#include "AuraController.generated.h"

//Enhanced Input
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class AURA_API AAuraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_Move;
	
	void Move(const FInputActionValue &Value);
	
	void CursorTrace();

	TScriptInterface<IEnemyInterface> ThisActor; // TScriptInterface is the correct way to hold interface pointers
	TScriptInterface<IEnemyInterface> LastActor;
};
