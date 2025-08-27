/*
 * File:        [BaseCharacter.h]
 * Description: [Parent class for characters]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[26/08/2025, Character alive stats variables]
 * Version:     [0.0.1]
 *
 * Notes:
 * - This is an abstract base class
 * - This class is intended to be inherited by character classes 
 *   (Player character, Enemy).
 * - Manages common character state, including position, textures, and
 *   animation frames.
 * 
 * Usage:
 * - Create a derived class from this class
 * - If a collision occurs, call UndoMovement() to revert the character to its
 *   position from the previous frame.
 * 
 */

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter{
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return worldPos; }
    void UndoMovement();
    virtual Rectangle GetCollisionRec();
    virtual void Tick(float deltaTime);
    virtual Vector2 GetScreenPos() = 0;
    bool GetAlive() { return alive; }
    void SetAlive(bool isAlive) { alive = isAlive; }

protected:
    // Textures
    Texture2D texture{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};
    Texture2D idle{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};;
    Texture2D run{LoadTexture("characters/Gordon/Unarmed_Run/Unarmed_Run_full.png")};

    // Position vectors
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // Direction - 1: facing right, -1: facing left
    float rightLeft{1.0f};

    // Animation variables
    float runningTime{};
    int frame{}; // current animation frame
    int maxFrames{6};
    const float kUpdateTime{1.0f / 12.0f};
    float speed{4.0f};
    Vector2 velocity{};


    // Sprite dimensions
    float width{};
    float height{};
    float scale{4.0f};

    // Character status
    bool alive{true};
};

#endif