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

// Tick - Base character
void BaseCharacter::Tick(float deltaTime){
    
    // Last frame position
    worldPosLastFrame = worldPos;
    
    // Update running time
    runningTime += deltaTime;
    
    // Update animation frame
    if (runningTime >= kUpdateTime){
        runningTime = 0.0;
        frame++;
        if (frame > maxFrames)
        frame = 0;
    }
    
    // Draw character
    Rectangle source{frame * width, 0.0f, width, height};
    Rectangle destRec{screenPos.x, screenPos.y, scale *width, scale *height};
    
    // Select different row from spritesheet
    source.y = ((rightLeft == 1.0f) ? 2.0f * source.height : 1.0f * source.height);
    DrawTexturePro(texture, source, destRec, Vector2{}, 0.0f, WHITE);
}   