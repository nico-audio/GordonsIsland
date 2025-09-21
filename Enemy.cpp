/*
 * File:        [Enemy.cpp]
 * Description: [Implements the Enemy class methods.]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[14/09/2025, Only implements AI behavior if target is set]
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

    if (target){
        
        cameraPos = target->GetWorldPos();

        /* Enemy AI - chase the target */

        // Vector from enemy to player character
        velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
        if (Vector2Length(velocity) < chaseRadius) velocity = {};

        // Deal damage
        if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
        {
            target->TakeDamage(damagePerSec * deltaTime);
            DrawText(TextFormat("-%.f", damagePerSec), 150, 80, 30, RED); // print damage
        }
    }
    else{
        // If target is null don't move
        velocity = {};
    }

    Character::Tick(deltaTime);
    
    /*
    // Get target screen position
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos()); // vector from enemy to character
    if (Vector2Length(velocity) < chaseRadius) velocity = {};
 
    Character::Tick(deltaTime);
 
    // Deal damage
    if (CheckCollisionRecs(target -> GetCollisionRec(), GetCollisionRec())){
        target -> TakeDamage(damagePerSec * deltaTime);
        DrawText(TextFormat("-%.f", damagePerSec), 150, 80, 30, RED); // print damage
    }
    */
    
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