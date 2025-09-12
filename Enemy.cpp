/*
 * File:        [Enemy.cpp]
 * Description: [Implements the Enemy class methods.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[04/09/2025, reset function]
 * Version:     [0.0.2]
 *
 * Notes:
 * 
 * Usage:
 *  - Defines the behavior for the enemy.
 *  - Checks if enemy is alive
 *  - Deals damage to target
 *  - Depends on raylib for input and drawing.
 *   
 */

 #include "raylib.h"
 #include "raymath.h"
 #include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture){
    worldPos = pos;
    initialPos = pos;
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}


// Collision box
Rectangle Enemy::GetCollisionRec(){
    float pad{30.0f}; // rectangle pad
    return Rectangle{
        GetScreenPos().x + pad,
        GetScreenPos().y + pad,
        (width * scale) - 2 * pad,
        (height * scale) - 2 * pad
    };
}


// Tick - Enemy update
void Enemy::Tick(float deltaTime){

    if (!GetAlive()) return;  // Check if enemy is alive
    
    /*Enemy AI - chase the target*/

    // Get target screen position
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos()); // vector from enemy to character
    if (Vector2Length(velocity) < chaseRadius) velocity = {};

    Character::Tick(deltaTime);

    // Deal damage
    if (CheckCollisionRecs(target -> GetCollisionRec(), GetCollisionRec())){
        target -> TakeDamage(damagePerSec * deltaTime);
        DrawText(TextFormat("-%.f", damagePerSec), 150, 80, 30, RED); // print damage
    }
}

// Returns the screen position
Vector2 Enemy::GetScreenPos(){
    return Vector2Subtract(worldPos, target->GetWorldPos());
}

void Enemy::Reset(){
    Character::Reset();
    worldPos = initialPos; // reset position
    target = nullptr; // forget the target
}