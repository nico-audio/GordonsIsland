/*
 * File:    [Character.cpp]
 * Description: [Implements the Character class methods. This file contains the
 *              logic for character movement, animation updates, and rendering.]
 * Author:  [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[26/08/2025, Draw weapon]
 * Version:     [0.0.1]
 * Notes:
 *  - Instantiated and used by main.cpp.
 *
 *
 * Usage:
 *  - Defines the behavior for the player character.
 *  - Depends on raymath for vector operations.
 *  
 */


#include "Character.h"
#include "raymath.h"

// Character constructor
Character::Character(int winWidth, int winHeight):
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height / sheetHeight;
}

// Returns the screen position
Vector2 Character::GetScreenPos(){
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}

// Tick - Character update
void Character::Tick(float deltaTime){
     
    // Gets WASD player input and returns a normalized velocity vector
    if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
    if (IsKeyDown(KEY_S)) velocity.y += 1.0;
    
    BaseCharacter::Tick(deltaTime);

    // Check for facing side
    Vector2 origin {};
    Vector2 offset {};
    float rotation {};
    if(rightLeft > 0.0f){
        origin = {0.0f, weapon.height * scale}; // facing right
        offset = {140.0f, 155.0f};
        weaponCollisionRec = {
            GetScreenPos().x + offset.x,
            GetScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = {35.0f};
    }
    else{
        origin = {weapon.width * scale, weapon.height * scale}; //facing left
        offset = {115.0f, 155.0f};
        weaponCollisionRec = {
            GetScreenPos().x + offset.x - weapon.width * scale,
            GetScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = {-35.0f};    
    }

    // Draw the weapon
    Rectangle source {0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest {GetScreenPos().x + offset.x, GetScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation,  WHITE);

    // Weapon debug
    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weapon.width * scale, weapon.height * scale, GREEN);
}