/*
 * File:        [BaseCharacter.cpp]
 * Description: [Defines the logic for the core character functionalities
 *               declared in BaseCharacter.h.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[04/09/2025, reset function]
 * Version:     [0.0.2]
 *
 * Notes:
 *   
 * 
 * Usage:
 *  - Depends on raylib for drawing.
 *  - Depends on raymath for vector operations.
 */

#include "raylib.h"
#include "raymath.h"
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
        GetScreenPos().x + pad,
        GetScreenPos().y + pad,
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
        if (frame > maxFrames) {
            frame = 0;
            if (isHurt) isHurt = false; // Hurt animation finished, revert state
        }
    }
    
    // Update movement
    if (Vector2Length(velocity) != 0.0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        rightLeft = ((velocity.x < 0.f) ? -1.0f : 1.0f);
    }

    // Animation state machine
    if(isHurt){
        if (texture.id != hurt.id) frame = 0; // Reset animation on state change
        texture = hurt;
        maxFrames = 6;
    } else {
        if (Vector2Length(velocity) != 0.0) {
            texture = run; // Switch to run animation
            maxFrames = 8;
        } else {
            texture = idle; // Switch to idle animation
            maxFrames = 12;
        }
    }

    velocity = {}; // reset velocity


    // Draw character
    Rectangle source{frame * width, 0.0f, width, height};
    Rectangle destRec{GetScreenPos().x, GetScreenPos().y, scale * width, scale * height};
    
    // Select different row from spritesheet
    source.y = ((rightLeft == 1.0f) ? 2.0f * source.height : 1.0f * source.height);
    DrawTexturePro(texture, source, destRec, Vector2{}, 0.0f, WHITE);

    
}

void BaseCharacter::Reset(){
    SetAlive(true);
}