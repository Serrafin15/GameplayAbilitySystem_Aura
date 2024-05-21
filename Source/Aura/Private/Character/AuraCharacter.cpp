// Copyright Alex Dominguez


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
    GetCharacterMovement()->bOrientRotationToMovement = true; // Changes rotation based on direction of movement (independent from camera)
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); // How fast it'll rotate
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false; // We don't want to use the controller's rotation 
    bUseControllerRotationRoll = false; // Controller rotation typically follows the camera's rotation
    bUseControllerRotationYaw = false;  // Therefore we don't want the character to always give its back to us since its a top down game.
}
