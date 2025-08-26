/*
 * File:        [Enemy.cpp]
 * Description: [Implements the Enemy class methods.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[26/08/2025, Get alive status]
 * Version:     [0.0.1]
 *
 * Notes:
 * 
 * Usage:
 *  - Defines the behavior for the enemy.
 *  - Checks if enemy is alive
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
    speed = 3.5f;
}

// Tick - Enemy update
void Enemy::Tick(float deltaTime){

    if (!GetAlive()) return;  // Check if enemy is alive
    
    /*Enemy AI - chase the target*/

    // Get target screen position
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
    BaseCharacter::Tick(deltaTime);
}

// Returns the screen position
Vector2 Enemy::GetScreenPos(){
    return Vector2Subtract(worldPos, target->GetWorldPos());
}