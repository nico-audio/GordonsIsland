/*
 * File:        [BaseCharacter.cpp]
 * Description: [Defines the logic for the core character functionalities
 *               declared in BaseCharacter.h.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[21/08/2025, Implemented constructor, UndoMovement, and GetCollisionRec]
 * Version:     [0.0.1]
 *
 * Notes:
 *   
 * 
 * Usage:
 *  
 */

#include "raylib.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){
   // constructor body
}

void BaseCharacter::UndoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec(){
    float pad{90.0f}; // rectangle pad
    return Rectangle{
        screenPos.x + pad,
        screenPos.y + pad,
        (width * scale) - 2 * pad,
        (height * scale) - 2 * pad
    };
}