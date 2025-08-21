/*
 * File:        [BaseCharacter.h]
 * Description: [Parent class for characters]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[21/08/2025, Create BaseCharacter class]
 * Version:     [0.0.1]
 *
 * Notes:
 * - This class is intended to be inherited by character classes 
 *   (Player character, Enemy).
 * - Manages common character state, including position, textures, and
 *   animation frames.
 * 
 * Usage:
 * - Create a derived class from this class
 * - If a collision occurs, call `UndoMovement()` to revert the character to its
 *   position from the previous frame.
 * 
 */

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter{
public:
    BaseCharacter();
    virtual void Tick(float deltaTime);
    Vector2 GetWorldPos() { return worldPos; }
    void UndoMovement();
    Rectangle GetCollisionRec();

protected:
    // Textures
    Texture2D texture{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};
    Texture2D idle{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};;
    Texture2D run{LoadTexture("characters/Gordon/Unarmed_Run/Unarmed_Run_full.png")};

    // Position vectors
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // Direction - 1: facing right, -1: facing left
    float rightLeft{1.0f};

    // Animation variables
    float runningTime{};
    int frame{}; // current animation frame
    int maxFrames{6};
    const float kUpdateTime{1.0f / 12.0f};
    const float kSpeed{4.0f};

    // Sprite dimensions
    float width{};
    float height{};
    float scale{4.0f};
};

#endif