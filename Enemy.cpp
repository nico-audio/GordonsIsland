/*
 * File:        [Enemy.cpp]
 * Description: [Implements the Enemy class methods.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[22/08/2025, Set enemy screen position]
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
 #include "raymath.h"
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
    screenPos = Vector2Subtract(worldPos, target -> GetWorldPos());
    BaseCharacter::Tick(deltaTime);
    
    // Add enemy AI
}