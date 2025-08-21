/*
 * File:        [Enemy.cpp]
 * Description: [Implements the Enemy class methods.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[21/08/2025, Create file]
 * Version:     [0.0.1]
 *
 * Notes:
 * 
 * Usage:
 *  - Defines the behavior for the enemy.
 *  - Depends on raylib for input and drawing.
 *   
 */

 #include "raylib.h"
 #include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture){
    worldPos = pos;
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = texture.width / maxFrames;
    height = texture.height;
}

// Tick - Enemy update
void Enemy::Tick(float deltaTime){
    
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
    Rectangle destRec{screenPos.x, screenPos.y, scale * width, scale * height};
    
    // Select different row from spritesheet
    source.y = ((rightLeft == 1.0f) ? 2.0f * source.height : 1.0f * source.height);
    DrawTexturePro(texture, source, destRec, Vector2{}, 0.0f, WHITE);
}