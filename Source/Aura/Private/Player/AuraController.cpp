// Copyright Alex Dominguez


#include "Player\AuraController.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "UObject/ScriptInterface.h"


AAuraController::AAuraController()
{
    
    bReplicates = true;
}

void AAuraController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    CursorTrace();
}

void AAuraController::CursorTrace()
{
    FHitResult CursorHit; 
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);  // Visibility collision channel, make sure enemy blueprints block the visibility channel on mesh
    if (!CursorHit.bBlockingHit) return; // If its not hitting anything then exit.

    LastActor = ThisActor; // What the actor was last frame
    ThisActor = CursorHit.GetActor(); // TScriptInterface allows us to store actor from FHitResult without casting.

    /** 
     * Line Trace from cursor. There are several scenarios
     * A. LastActor == null && ThisActor == null
     *     -Do Nothing
     * B.LastActor == null && ThisActor is valid
     *      -Highlight ThisAcor
     * C. LastActor == valid && ThisActor is null
     *      -UnHighlight LastActor
     * D. Both valid. but LastActor != ThisActor
     *      -UnHighlight LastActor and Highlight ThisActor
     * E. Both actors are valid, and are the same actor
     *      -Do nothing
    */

   if(LastActor == nullptr)
   {
    
        if(ThisActor != nullptr)
        {
            //Case B:
            ThisActor->HighlightActor();
        }
        else
        {
            //Case A: Both are null, do nothing
        }

   }
   else
   {
        //LastActor is valid
        if(ThisActor == nullptr)
        {
            //Case C:
            LastActor->UnHighlightActor();
        }
        else
        {
            //Both actors are valid
            if(LastActor != ThisActor)
            {
                //Case D
                LastActor->UnHighlightActor();
                ThisActor->HighlightActor();
            }
            else
            {
                // Case E: Do Nothing
            }   
        }
   }
    

}

void AAuraController::BeginPlay()
{
    Super::BeginPlay();
    check(AuraContext); // Check if the aura context is set, if it isn't (nullptr), then the game will crash.   (check() is known as an assert)

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem) // Same as if(Subsystem == nullptr) return;
    Subsystem->AddMappingContext(AuraContext, 0);

    bShowMouseCursor = true; 
    DefaultMouseCursor = EMouseCursor::Default; //Changes cursor

    FInputModeGameAndUI InputModeData; //InputMode Struct allows use of input from key and mouse and to affect UI(widgets)
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Doesn't lock the mouse to viewport
    InputModeData.SetHideCursorDuringCapture(false); // Doesn't hide cursor while cursor is in viewport

    SetInputMode(InputModeData); // Sets data


}

void AAuraController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); // If cast fails it crashes
    EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAuraController::Move);
}

void AAuraController::Move(const FInputActionValue &Value)
{
    const FVector2D InputAxisVector = Value.Get<FVector2D>();
   
    const FRotator Rotation = GetControlRotation(); // Gets controller rotation
    const FRotator YawRotation(0.f, Rotation.Yaw, 0); // Sets pitch and roll to 0 so only the yaw is changed when yaw is 0 the character is looking forward
    
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Gives us the forward vector coresponding to yaw rotation

    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Right Vector

    if(APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
    }


}


