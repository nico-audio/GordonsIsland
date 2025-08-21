/*
 * File:    [Character.cpp]
 * Description: [Implements the Character class methods. This file contains the
 *              logic for character movement, animation updates, and rendering.]
 * Author:  [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[20/08/2025, Implemented GetCollisionRec]
 * Version:     [0.0.1]
 * Notes:
 *  - Instantiated and used by main.cpp.
 *
 *
 * Usage:
 *  - Defines the behavior for the player character.
 *  - Depends on raylib for input and drawing.
 *  - Depends on raymath for vector operations.
 *  
 */


#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight){
    width = texture.width / maxFrames;
    height = texture.height / sheetHeight;
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}

// Tick - Character update
void Character::Tick(float deltaTime){

    BaseCharacter::Tick(deltaTime);

    // Gets WASD player input and returns a normalized direction vector
    Vector2 direction{};

    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;

    // Movement
    if (Vector2Length(direction) != 0.0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), kSpeed));
        rightLeft = ((direction.x < 0.f) ? -1.0f : 1.0f);
        texture = run; // Switch to run animation
        maxFrames = 8;
    }
    else {
        texture = idle; // Switch to idle animation
        maxFrames = 12;
    }
}