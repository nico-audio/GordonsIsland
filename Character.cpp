/*
 * File:    [Character.cpp]
 * Description: [Implements the Character class methods. This file contains the
 *              logic for character movement, animation updates, and rendering.]
 * Author:  [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[18/08/2025, Implemented constructor, Tick, and SetScreenPos]
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

Character::Character(){
    width = texture.width / maxFrames;
    height = texture.height / sheetHeight;
}

void Character::SetScreenPos(int winWidth, int winHeight){
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}

// Tick - Character update
void Character::Tick(float deltaTime){
    
    // Last frame position
    worldPosLastFrame = worldPos;

    // Gets WASD player input and returns a normalized direction vector
    Vector2 direction{};

    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;

    // Movement
    //Vector2 direction = getInputDirection();
    if (Vector2Length(direction) != 0.0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), kSpeed));
        rightLeft = ((direction.x < 0.f) ? -1.0f : 1.0f);
        texture = run;
        maxFrames = 8.0f;
    }
    else {
        texture = idle;
        maxFrames = 12.0f;
    }

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
    Rectangle destRec{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    
    // Select different row from spritesheet
    source.y = ((rightLeft == 1.0f) ? 2.0f * source.height : 1.0f * source.height);
    DrawTexturePro(texture, source, destRec, Vector2{}, 0.0f, WHITE);
}

void Character::UndoMovement(){
    worldPos = worldPosLastFrame;
}