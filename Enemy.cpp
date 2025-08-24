/*
 * File:        [Enemy.cpp]
 * Description: [Implements the Enemy class methods.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[24/08/2025, Enemy AI - Chase the target]
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
    speed = 3.5f;
}


// Tick - Enemy update
void Enemy::Tick(float deltaTime){
    
    /*Enemy AI - chase the target*/ 
    
    // Get target screen position and nomalize vector
    Vector2 toTarget = Vector2Subtract(target -> GetScreenPos(), screenPos);
    toTarget = Vector2Normalize(toTarget);
    
    // toTarget gets the length of speed
    toTarget = Vector2Scale(toTarget, speed);
    
    // Move the enemy  
    worldPos = Vector2Add(worldPos, toTarget); 
    screenPos = Vector2Subtract(worldPos, target -> GetWorldPos());
    BaseCharacter::Tick(deltaTime);
    
}